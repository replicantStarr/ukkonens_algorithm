#include "json.hpp"
#include <iostream>
#include <fstream>
#include "suffix_tree.hpp"
#include <string>
#include <stdexcept>
#include <queue>

using json = nlohmann::json;

namespace Test_Runner {
	struct Result {
		bool Passed;
		std::string Message;
	};

	void assert_node(Suffix_Tree::Node* node, json exp_node) {
		if (node->Ind->a != exp_node["Edge"][0] 
				|| node->Ind->b != exp_node["Edge"][1]
				|| node->Child_Nodes.size() != exp_node["Edge"]["Children"].size()) {
			throw std::runtime_error("Nodes are not equal");
		}
	}

	void assert_result(Suffix_Tree::Node* res_node, json exp) {
		std::queue<Suffix_Tree::Node*> res_queue;
		std::queue<json> json_queue;

		res_queue.push_back(res_node);
		json_queue.push_back(exp["0"]);
		
		while(!res_queue.empty()) {
			Suffix_Tree::Node* top = res_queue.top();
			json exp_top = json_queue.top();

			res_queue.pop();
			json_queue.pop();

			assert_node(top, exp_top);

			for (int i = 0; i < top->Child_Nodes.size(); ++i) {
				res_queue.push_back(top->Child_Nodes[i]);
				json_queue.push_back(top->Children[i]);
			}
		}
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
