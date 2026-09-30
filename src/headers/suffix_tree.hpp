#ifndef SUFFIX_TREE_HPP
#define SUFFIX_TREE_HPP

#include <string>
#include <memory>
#include <unordered_map>

namespace Suffix_Tree {
	// Simply contains the indices of a substring [a,b] of word.  This is far more efficient than an array.
	struct Ind {
		int a;

		// Allows for really simple indexing, the algorithm can simply increase the value on the heap and all leaf nodes can point to the same int.
		std::shared_ptr<int> b;

	};

	// A struct to contain all data of the nodes in a suffix tree.  A tree doesn't exist only its nodes.
	struct Node {
		// Each node contains a unique suffix -- this is equivalent to the suffix of it's incoming edge.
		std::unique_ptr<Ind> Indices;

		// Can check if a suffix is already created and return it's node in constant time.
		std::unordered_map<char, std::unique_ptr<Node>> Children;
	};


	// Contains necessary positional data on where in the tree is currently being processed
	struct Active_Point { 
		// The parent of the current edge which is being operated on
		Node* Parent;

		// The incoming edge to a node, which is also a child edge of the parent node
		Node* Edge;

		// The length of the current compressed edge
		int Length;
	};

	// Safely returns the terminal symbol when indexing
	char get_char(std::string w, int i);

	// Returns a pointer to the root node of a suffix tree.  Using the root node traversal is possible.
	std::unique_ptr<Node> create(std::string word); 
}

#endif
