#include "suffix_tree.hpp"
#include <string>
#include <memory>
#include <iostream>
#include <utility>

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
	
	std::unique_ptr<Node> create(std::string word) {
		// Keeps track of current edge root node, edge character and edge length -- all 3 crucial to Ukkonen's
		Active_Point active_point;

		// Root node has no character and no incoming edge
		std::unique_ptr<Node> root_node = std::make_unique<Node>(nullptr);

		// Assign the root to being the current active node
		active_point.Root = root_node.get();

		// The number of suffixes currently required to be inserted
		int remainder = 1;

		// Our index of the current character being processed in word
		int i = 0;

		// We only need to loop while there are suffixes to add.
		while (remainder && i < word.size()) {

			// EXTENSION RULE 1 -> If current word[a, b] is on a leaf edge, and i = b + 1 || b = -1, then add s[i] to the end of the edge.
			if (active_point.Root->Children[word[i]] == nullptr) {

				// If the active node is the main root, no edge exists so just start from 0
				// Otherwise actually use the end of the last node to continue the string
				std::cout << active_point.Root->Edge << std::endl;	
				int start = active_point.Root->Edge ? active_point.Root->Edge->a : 0;

				// -1 means the current index of i, that way we dont need manually update each operation
				std::unique_ptr<Ind> ind = std::make_unique<Ind>(start, -1);

				// Push the new node into the root to create an edge
				active_point.Root->Children[word[i]] = (std::make_unique<Node>(std::move(ind)));

				// Now loop to the next suffix
				++i;
				
				// Suffix is added so no remainder
				remainder = 0;
				continue;
			}

			// word[i] now ends on a non-leaf edge.

			// EXTENSION RULE 2 -> word[a, b] exists such that word[b + 1] != word[i], and therefore the edge must now be split into
			// word[a, L], where L is the current active length, and 2 children of [i, -1] and b[L, -1].
			if (word[active_point.Length] != word[i]) {
				// This is the new suffix added
				std::unique_ptr<Ind> ind = std::make_unique<Ind>(i, -1);
				
				// This is the existing suffix being split and linked
				std::unique_ptr<Ind> ind2 = std::make_unique<Ind>(active_point.Length, -1);

				// Create a node with new suffix
				std::unique_ptr<Node> new_node = std::make_unique<Node>(std::move(ind));
				
				// Create a node with split existing suffix
				std::unique_ptr<Node> e_node = std::make_unique<Node>(std::move(ind2));

				// Add new nodes as child nodes to split edge


			}

		}

		return root_node;
	}
}
