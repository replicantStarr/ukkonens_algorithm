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
		
		std::cout << "test" << std::endl;

		std::unique_ptr<Node> root_node = std::make_unique<Node>(nullptr);

		std::cout << "test" << std::endl;

		// No rules implemented yet, let's just add all nodes to root first.
		for (auto i = 0; i < word.size(); ++i) {
			// Simple node with 1 char empty children.
		}

		return root_node;
	}
}
