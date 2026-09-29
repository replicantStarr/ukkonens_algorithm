#include "suffix_tree.hpp"
#include <string>
#include <memory>
#include <iostream>
#include <stdexcept>

namespace Suffix_Tree {
	/*
	 * Some notes on Ukkonen's before implementation
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
	char getchar(std::string word, int index) {
		if (index < word.size()) return word[index];
		if (index == word.size()) return '$';
		throw new std::runtime_error("Index has no character");
	}
	
	std::unique_ptr<Node> create(std::string word) {
		// Keeps track of current edge root node, edge character and edge length -- all 3 crucial to Ukkonen's
		Active_Point active_point;

		// Root node has no character and no incoming edge
		std::unique_ptr<Node> root_node = std::make_unique<Node>(nullptr);

		// Assign the root to being the current active node
		active_point.Root = root_node.get();
		active_point.Length = 0;

		// The number of leftover suffixes skipped to be inserted later
		int remainder = 0;

		// Our index of the current character being processed in word
		std::shared_ptr<int> i = std::make_shared<int>(0);

		// We only need to loop while there are suffixes to add.
		while (*i <= word.size()) {

			if (!remainder) ++remainder;

			std::cout << "i " << i << std::endl;
			// EXTENSION RULE 1 -> If current word[a, b] is on a leaf edge, and i = b + 1 || b = -1, then add s[i] to the end of the edge.
			if (active_point.Root->Children[word[*i]] == nullptr) {
				std::cout << "t1" << std::endl;
				// If the active node is the main root, no edge exists so just start from 0
				// Otherwise actually use the end of the last node to continue the string
				std::cout << active_point.Root->Edge << std::endl;	
				int start = active_point.Root->Edge ? active_point.Root->Edge->a : 0;

				// Point to the current index, it will increase each loop;
				std::unique_ptr<Ind> ind = std::make_unique<Ind>(start, i);

				// Push the new node into the root to create an edge
				active_point.Root->Children[word[*i]] = std::make_unique<Node>(std::move(ind));

				// Suffix is inserted
				--remainder;

				std::cout << "testing" << std::endl;
			}

			// EXTENSION RULE 2 -> word[a, b] exists such that word[b + 1] != word[i], and therefore the edge must now be split into
			// word[a, L], where L is the current active length, and 2 children of [i, -1] and b[L, -1].
			else if (word[active_point.Length] != word[*i]) {	
				std::cout << "o2" << std::endl;
				// Assign the active edge to the edge outgoing from the root which is equal to first char of the suffix.
				active_point.Edge = active_point.Root->Children[word[*i]].get();

				// This is the new suffix added
				std::unique_ptr<Ind> ind = std::make_unique<Ind>(*i, i);
				
				// This is the existing suffix being split and linked
				std::unique_ptr<Ind> ind2 = std::make_unique<Ind>(active_point.Edge->Edge->a + active_point.Length, i);

				// Add new nodes as child nodes to split edge
				active_point.Edge->Children[word[*i]] = std::make_unique<Node>(std::move(ind));
				active_point.Edge->Children[word[active_point.Length]] = std::make_unique<Node>(std::move(ind2));

				// Update the active node edge to only go from [a, L]
				active_point.Edge->Edge->b = std::make_shared<int>(active_point.Edge->Edge->a + active_point.Length);

				// Suffix was inserted
				--remainder;

				// Reset to active root for remainder suffixes to be inserted (just a rerun with 1 less char)
				active_point.Root = root_node.get();
				active_point.Edge = nullptr;
				if (active_point.Length) --active_point.Length;

				// Move the next char if there are no remainders
				if (!remainder) ++*i;
				continue;
			}
			
			// EXTENSION RULE 3 -> word[a, b] exists such that word[b + 1] = word[i].  This means the next char should be processed so length is bumped.
			else {
				// We know for next suffix all letters will equal, bump it so that they only check the newest one
				active_point.Length++;
				
				// The current suffix was not inserted so it's now a remainder
				++remainder;
			}

			++*i;
		}

		return root_node;
	}
}
