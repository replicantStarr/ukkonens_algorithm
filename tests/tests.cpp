#define DOCTEST_CONFIG_IMPLEMENT
#include "doctest.h"

int main(int argc, char** argv) {
	return doctest::Context(argc, argv).run();
}

TEST("Empty string returns single root node") { }

TEST("Single character string returns single node") { }

TEST("Simple two word string returns two separate nodes") { }

TEST("basic string 1") { }

TEST("Basic string 2") { }

TEST("String with 2 repeated characters") { }

TEST("Long string returns long tree") { }

TEST("Triple repeition string") { }
