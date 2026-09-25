#include "json.hpp"
#include <iostream>
#include <fstream>
#include "suffix_tree.hpp"
#include <string>
#include <stdexcept>

using json = nlohmann::json;

namespace Test_Runner {
	struct Result {
		bool Passed;
		std::string Message;
	};

	void assert_result(Suffix_Tree::Node* res_node, json exp) {
		throw std::runtime_error("Assertion Failed");
	}

	Result run_test(json test) {
		std::cout << test["word"] << std::endl;
		Suffix_Tree::Node* result = Suffix_Tree::create(test["word"].get<std::string>());

		Result test_result;
		try {
			assert_result(result, test["exp"]);
		}
		catch (const std::exception& ex) {
			test_result.Passed = false;
			test_result.Message = ex.what();
		}

		return test_result;
	}

	void load_tests() {
		std::ifstream file(TESTS_PATH);
		json data = json::parse(file);

		int passed = 0;
		int failed = 0;

		for (const auto& t_case: data["Test_Cases"]) {	
			std::cout << t_case << std::endl;
			Result result = run_test(t_case);
			std::cout << result.Passed << std::endl;
			std::cout << result.Message << std::endl;
		}

		std::cout << "Passed " << passed << " tests" << std::endl;
		std::cout << "Failed " << failed << " tests" << std::endl;
	}
}

int main() {
	std::cout << "Running Tests" << std::endl;
	Test_Runner::load_tests();
	return 0;
}
