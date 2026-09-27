#include "suffix_tree.hpp"
#include <string>
#include <memory>
#include <iostream>

namespace Suffix_Tree {
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
