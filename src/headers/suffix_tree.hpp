#ifndef SUFFIX_TREE_HPP
#define SUFFIX_TREE_HPP

#include <string>
#include <vector>

namespace Suffix_Tree {
	
	// Simply contains the indices of a substring [a,b] of word.  This is far more efficient than an array.
	struct Ind {
		int a;
		int b;
	};

	// A struct to contain all data of the nodes in a suffix tree.  A tree doesn't exist only its nodes.
	struct Node {
		// Each node contains a unique suffix -- this is equivalent to the suffix of it's incoming edge.
		Ind Suffix;
		
		// Each node must be able to go to any child node, this can simply be stored as an array and looped over.
		// I have thoughts on a possible optimisation here, first I want to get an implementation though.
		std::vector<Node*> Child_Nodes;
	};

	// Contains necessary positional data on where in the tree is currently being processed
	struct Active_Point { 
		// The root of the current edge which is being operated on
		Node* Root_Node;

		// The exact char in a compressed edge which is being operated.
		char Edge;

		// The length of the current compressed edge
		int Length;
	};

	// Returns a pointer to the root node of a suffix tree.  Using the root node traversal is possible.
	Node* create(std::string word); 
}

#endif
