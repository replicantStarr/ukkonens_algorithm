#include "json.hpp"
#include <iostream>
#include <fstream>
#include "suffix_tree.hpp"
#include <string>
#include <stdexcept>
#include <queue>
#include <memory>

using json = nlohmann::json;

namespace Test_Runner {
	struct Result {
		bool Passed;
		std::string Message;
	};

	void assert_node(Suffix_Tree::Node* node, json exp_node) {
		if (node->Edge->a != exp_node["Edge"][0] 
				|| node->Edge->b != exp_node["Edge"][1]
				|| node->Child_Nodes.size() != exp_node["Edge"]["Children"].size()) {
			throw std::runtime_error("Nodes are not equal");
		}
	}

	void assert_result(Suffix_Tree::Node* res_node, json exp) {
		std::queue<Suffix_Tree::Node*> res_queue;
		std::queue<json> json_queue;

		res_queue.push(res_node);
		json_queue.push(exp["0"]);
		
		while(!res_queue.empty()) {
			Suffix_Tree::Node* top = res_queue.front();
			json exp_top = json_queue.front();

			res_queue.pop();
			json_queue.pop();

			assert_node(top, exp_top);

			for (int i = 0; i < top->Child_Nodes.size(); ++i) {
				res_queue.push(top->Child_Nodes[i].get());
				json_queue.push(exp_top["Children"][i]);
			}
		}
	}

	Result run_test(json test) {
		std::cout << test["word"] << std::endl;
		std::unique_ptr<Suffix_Tree::Node> result = Suffix_Tree::create(test["word"].get<std::string>());

		Result test_result;
		try {
			if (result == nullptr) {
				throw std::runtime_error("Null pointer returned");
			}
			assert_result(result.get(), test["exp"]);
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

		for (const auto& [t_name, t_case]: data["Cases"].items()) {
			std::cout << t_name << '\n' << std::endl;
			Result res = run_test(t_case);
			if (!res.Passed) {
				std::cout << "TEST FAILED" << std::endl;
				std::cout << res.Message << '\n' << std::endl;
				failed++;
				continue;
			}

			std::cout << "TEST PASSED" << std::endl;
			std::cout << '\n' << std::endl;
			passed++;
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
