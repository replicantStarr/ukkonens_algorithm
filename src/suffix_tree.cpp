#include "suffix_tree.hpp"
#include <string>
#include <memory>
#include <iostream>

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

		// The number of suffixes currently required to be inserted
		int remainder = 1;

		// Our index of the current character being processed in word
		int i = 0;

		// We only need to loop while there are suffixes to add.
		while (remainder) {
			// If the string is not currently in the node then add it.
			if (active_point->Root->Suffixes.find(word[i]) == active_point->Root->Suffixes.end()) {
				// If the active node is the main root, no edge exists so just start from 0
				// Otherwise actually use the end of the last node to continue the string
				int start = active_point->Root->Edge ? 0 : active_point->Root->Edge->b;
				std::unique_ptr<Ind> ind = std::make_unique<Ind>(start);
			}
		}
		return root_node;
	}
}
