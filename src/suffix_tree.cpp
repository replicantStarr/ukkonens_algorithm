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
		
		std::unique_ptr<Node> root_node = std::make_unique<Node>(nullptr);
		// No rules implemented yet, let's just add all nodes to root first.
		for (auto i = 0; i < word.size(); ++i) {
			// Simply adding child node to root node
			std::unique_ptr<Ind> k = std::make_unique<Ind>(i, i + 1);
			std::unique_ptr<Node> n = std::make_unique<Node>();
			n->Edge = std::move(k);
			root_node->Child_Nodes.push_back(std::move(n));
		}

		return root_node;
	}
}
