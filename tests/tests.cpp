#define DOCTEST_CONFIG_IMPLEMENT
#include "doctest.h"
#include "suffix_tree.hpp"

int main(int argc, char** argv) {
	return doctest::Context(argc, argv).run();
}

bool assert_ind(Suffix_Tree::Ind& ind, int a, int b) {
	return ind.a == a && ind.b == b;
}

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
	
}

TEST_CASE("Simple two word string returns two separate nodes") { }

TEST_CASE("basic string 1") { }

TEST_CASE("Basic string 2") { }

TEST_CASE("String with 2 repeated characters") { }

TEST_CASE("Long string returns long tree") { }

TEST_CASE("Triple repeition string") { }
