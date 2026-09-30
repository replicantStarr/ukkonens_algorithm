#include "suffix_tree.hpp"

namespace Suffix_Tree {
	// Returns word[i] of index otherwise $ for terminal processing
	char get_char(const std::string w, int i) {
		if (i != w.size()) return w[i];
		else return '$';
	}

	// The implementation of Ukkonen's algorithm which constructs a suffix tree
	// This is without suffix links, with a worst case upper bound of O(n^2)
	std::unique_ptr<Node> create(std::string word) {
		// Root node has no character and no incoming edge
		std::unique_ptr<Node> root_node = std::make_unique<Node>(nullptr);

		// Keeps track of current parent node, edge and index of comparison with length -- all 3 crucial to Ukkonen's
		Active_Point active;

		// The algorithm begins by operating on the root node
		active.Parent = root_node.get();

		// No outgoing edges exist yet to process
		active.Edge = nullptr;
		active.Length = 0;

		// The number of leftover suffixes skipped to be inserted later
		int remainder = 0;

		// EXTENSION RULE 1 -> Automatically updates word[a, i] such that the leaf edge extends each iteration.
		std::shared_ptr<int> i = std::make_shared<int>(0);

		// We only need to loop while there are suffixes to add.
		while (*i <= word.size()) {

			// First find a candidate edge with the same prefix
			std::unordered_map<char, std::unique_ptr<Node>>::const_iterator find_edge = active.Parent->Children.find(get_char(word, *i - active.Length));

			// EXTENSION RULE 2.i -> When there is no such child node of word[i] at active parent, then create a new node and add
			if (find_edge == active.Parent->Children.end()) {

				// Indices are from current character to index
				std::unique_ptr<Ind> ind = std::make_unique<Ind>(*i, i);

				// Creating the new child node
				active.Parent->Children[get_char(word, *i - active.Length)] = std::make_unique<Node>(std::move(ind));

				// Suffix inserted so one less total suffixes remain, otherwise move to next index
				if (remainder > 0) --remainder;
				else ++*i;

				// Starts from the top every time or else would be creating non-existant suffixes
				active.Parent = root_node.get();
				active.Edge = nullptr;

				// Current suffix has been inserted, move to next with reset length
				active.Length = remainder;

				continue;
			}

			// The found edge is now traversed down because of equal prefixes
			active.Edge = find_edge->second.get();

			// There must always be a character to process.
			// If it's too large, step down to the next node and continue
			if (active.Length >= *active.Edge->Indices->b - active.Edge->Indices->a) {
				active.Parent = active.Edge;
				active.Length -= *active.Edge->Indices->b - active.Edge->Indices->a;
				active.Edge = nullptr;

				continue;
			}

			// EXTENSION RULE 2.ii -> word[a, b) exists such that word[b] != word[*i], and therefore the edge must now be split
			// word[a, a + l), where l is the current active length, with 2 children of n1[*i, i) and n2[b, *i).

			// There is an edge which exists, we must traverse it and split at the unequal index
			if (get_char(word, active.Edge->Indices->a + active.Length) != get_char(word, *i)) {

				// This is the new suffix added
				std::unique_ptr<Ind> ind = std::make_unique<Ind>(*i, i);

				// This is the existing suffix bottom half being split
				std::unique_ptr<Ind> ind2 = std::make_unique<Ind>(active.Edge->Indices->a + active.Length, active.Edge->Indices->b);

				// Update the active node edge to only be the active length from a
				active.Edge->Indices->b = std::make_shared<int>(active.Edge->Indices->a + active.Length);

				// Create split edge from original edge
				std::unique_ptr<Node> bottom_edge = std::make_unique<Node>(std::move(ind2));

				// Simply move the existing hashmap of children
				bottom_edge->Children = std::move(active.Edge->Children);

				// Clears the children which are no longer linked to upper half of the old edge
				active.Edge->Children.clear();

				// Add new nodes as child nodes to split edge
				active.Edge->Children[get_char(word, *i)] = std::make_unique<Node>(std::move(ind));
				active.Edge->Children[get_char(word, active.Edge->Indices->a + active.Length)] = std::move(bottom_edge);

				// Suffix inserted so one less total suffixes remain, otherwise move to next index
				if (remainder > 0) --remainder;
				else ++*i;

				// Reset to root for remainder suffixes to be inserted (just a rerun with 1 less char)
				active.Parent = root_node.get();
				active.Edge = nullptr;

				// Current suffix has been inserted, must move onto the next such that length resets
				active.Length = remainder;

				continue;
			}

			// EXTENSION RULE 3 -> word[a, b) exists such that word[b + 1] = word[i].  This means the next char should be processed so length is bumped.
			else {

			    // A suffix is skipped to be inserted later, so its a new remainder
				++remainder;

				// We know for next suffix all letters will equal, bump it so that they only check the newest one
				++active.Length;
			}

			++*i;
		}

		return root_node;
	}
}
