#ifndef SUFFIX_TREE_HPP
#define SUFFIX_TREE_HPP

#include <string>

namespace Suffix_Tree {
	// A struct to contain all data of the nodes in a suffix tree.  A tree doesn't exist only its nodes.
	struct Suffix_Node { }

	// Contains necessary positional data on where in the tree is currently being processed
	struct Active_Point { }

	// Returns a pointer to the root node of a suffix tree.  Using the root node traversal is possible.
	Suffix_Node* Create(std::string) { }
}
