#include "suffix_tree.hpp"
#include <string>
#include <memory>

namespace Suffix_Tree {
	// Returns the root node of a constructed suffix tree based on any given word
	// Construction is done using Ukkonen's algorithm
	std::unique_ptr<Node> create(std::string word) {

		// Keeps track of current edge root node, edge character and edge length -- all 3 crucial to Ukkonen's
		Active_Point active_point;

		// No rules implemented yet, let's just add all nodes to root first.
		for (int i = 0; i < word.size(); ++i) {
			// Simple node with 1 char empty children.
		}

		return nullptr;
	}
}
