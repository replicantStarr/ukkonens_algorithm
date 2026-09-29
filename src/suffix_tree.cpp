#include "suffix_tree.hpp"
#include <string>
#include <memory>
#include <iostream>
#include <stdexcept>

namespace Suffix_Tree {

	/*
	 * Some notes on Ukkonen's before implementation with extension rules
	 * 1. For each suffix, s[i, j], the suffixes s[i + n, j] are also processed until i + n = j.  E.g. abc = abc, bc, c
	 * 2. There are a few different rules for processing:
	 * 	i. If string s[i, j] end at a leaf edge, then s[j + 1] is just added
	 * 	ii. If string s[i, j] ends at a non-leaf edge:
	 * 		a. If s[j + 1] does not equal current character c, then create a node from [1, j], then [j, j + 1]
	 * 		b. Otherwise, simply do nothing
	 */
	// Returns the root node of a constructed suffix tree based on any given word
	// Construction is done using Ukkonen's algorithm
	//

	// Simple function to take whatever the current word is and at the terminal $
	// This is very important for processing
	char get_char(std::string w, int i) {
		if (i < w.size()) return w[i];
		if (i == w.size()) return '$';
		throw new std::runtime_error("Index has no character");
	}

	std::unique_ptr<Node> create(std::string word) {
		// Keeps track of current edge root node, edge character and edge length -- all 3 crucial to Ukkonen's
		Active_Point active_point;

		// Root node has no character and no incoming edge
		std::unique_ptr<Node> root_node = std::make_unique<Node>(nullptr);

		// The algorithm begins by operating on the root node
		active_point.Root = root_node.get();
		
		// No outgoing edges exist yet to process
		active_point.Edge = nullptr;
		active_point.Length = 0;

		// The number of leftover suffixes skipped to be inserted later
		int remainder = 0;

		// EXTENSION RULE 1 -> Automatically updates word[a, i] such that the leaf edge extends each iteration.
		std::shared_ptr<int> i = std::make_shared<int>(0);

		// We only need to loop while there are suffixes to add.
		while (*i <= word.size()) {
			// EXTENSION RULE 2 -> word[a, b] exists such that word[b + 1] != word[*i], and therefore the edge must now be split 
			// word[a, L], where L is the current active length, with 2 children of [*i, i] and b[L, *i].
			
			// When no edge exists, it's simply comparing word[i] to an empty string, which essentially is a garunteed split
			if (active_point.Root->Children.find(get_char(word, *i - active_point.Length)) == active_point.Root->Children.end()) {
				
				// Indices are from current character to index
				std::unique_ptr<Ind> ind = std::make_unique<Ind>(*i, i);

				// Creating the new child node
				active_point.Root->Children[get_char(word, *i - active_point.Length)] = std::make_unique<Node>(std::move(ind));

				// remainder can never be less than 0, if it is we have nothing else to loop so go to next index
				if (remainder > 0) --remainder;
				else ++*i;

				// Starts from the top every time or else would be creating non-existant suffixes
				active_point.Root = root_node.get();
				active_point.Edge = nullptr;
				--active_point.Length;
				continue;
			}
			

			// There is an edge which exists, we must traverse it and split at the unequal index
			if (get_char(word, active_point.Edge->Edge->a + active_point.Length) != get_char(word, *i)) {

				// This is the new suffix added
				std::unique_ptr<Ind> ind = std::make_unique<Ind>(*i, i);

				// This is the existing suffix being split and linked
				std::unique_ptr<Ind> ind2 = std::make_unique<Ind>(active_point.Edge->Edge->a + active_point.Length, i);

				// Update the active node edge to only go from [a, L]
				active_point.Edge->Edge->b = std::make_shared<int>(active_point.Edge->Edge->a + active_point.Length);

				// Create split edge from original edge
				std::make_unique<Node> bottom_edge = std::make_unique<Node>(std::move(ind2));

				// Simply move the existing hashmap of children
				bottom_edge->Children = std::move(active_point.Edge->Children);
				active_point.Edge->Children.clear();

				// Add new nodes as child nodes to split edge
				active_point.Edge->Children[get_char(word, *i)] = std::make_unique<Node>(std::move(ind));
				active_point.Edge->Children[get_char(word, active_point.Length)] = std::move(bottom_edge);

				// Reset to active root for remainder suffixes to be inserted (just a rerun with 1 less char)
				active_point.Root = root_node.get();
				active_point.Edge = nullptr;
				if (active_point.Length) --active_point.Length;

				if (remainder > 0) --remainder;
				else ++*i;
				continue;
			}
			
			// EXTENSION RULE 3 -> word[a, b] exists such that word[b + 1] = word[i].  This means the next char should be processed so length is bumped.
			else {
				++remainder;
				// We know for next suffix all letters will equal, bump it so that they only check the newest one
				++active_point.Length;
			}

			++*i;
		}

		return root_node;
	}
}
