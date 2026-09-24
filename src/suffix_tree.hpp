#ifndef SUFFIX_TREE_HPP
#define SUFFIX_TREE_HPP

#include <string>

namespace Suffix_Tree {
	
	// Simply contains the indices of a substring [a,b] of word.
	struct Suffix_Ind {
		int a;
		int b;
	}

	// A struct to contain all data of the nodes in a suffix tree.  A tree doesn't exist only its nodes.
	struct Suffix_Node {
		Suffix_Ind Suffix;
		std::array<Suffix_Node*> Child_Nodes;
	}

	// Contains necessary positional data on where in the tree is currently being processed
	struct Active_Point { 
		Suffix_Node* Node;
		char Edge;
		int Length;
	}

	// Returns a pointer to the root node of a suffix tree.  Using the root node traversal is possible.
	Suffix_Node* Create(std::string) { }
}
