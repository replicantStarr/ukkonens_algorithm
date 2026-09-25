#include "suffix_tree.hpp"

int main(int argc, char** argv) {
	return doctest::Context(argc, argv).run();
}

bool assert_ind(Suffix_Tree::Ind& ind, int a, int b) {
	return ind.a == a && ind.b == b;
}

bool assert_children(std::vector<Suffix_Tree::Node*> nodes, std::vector<Suffix_Tree::Node*> expected_nodes) {}

Suffix_Tree::Node root_node() {
	Suffix_Tree::Ind ind{0, 0};
	Suffix_Tree::Node node{ind, {}};
	return node;
}

TEST_CASE("Empty string returns single root node") { 
	Suffix_Tree::Ind ind{0, 0};
	Suffix_Tree::Node* result = Suffix_Tree::create("");

	REQUIRE(result != nullptr); 
	REQUIRE(assert_ind(result->Suffix, 0, 0)); 
	REQUIRE(result->Child_Nodes.empty());
}

TEST_CASE("Single character string returns single node") { 
	Suffix_Tree::Node root = root_node();
	Suffix_Tree::Node a = Suffix_Tree::Node{{0, 1}, {}};
	root.Child_Nodes.push_back(a);

	Suffix_Tree::Node* result = Suffix_Tree::create("a");

	REQUIRE(result != nullptr);
	REQUIRE(root.Child_Nodes.size() == 1);
	REQUIRE(root.Child_Nodes.size()
}

TEST_CASE("Simple two word string returns two separate nodes") { }

TEST_CASE("basic string 1") { }

TEST_CASE("Basic string 2") { }

TEST_CASE("String with 2 repeated characters") { }

TEST_CASE("Long string returns long tree") { }

TEST_CASE("Triple repeition string") { }
