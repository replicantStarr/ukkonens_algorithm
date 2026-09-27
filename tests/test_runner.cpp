#include "json.hpp"
#include <iostream>
#include <fstream>
#include "suffix_tree.hpp"
#include <string>
#include <stdexcept>
#include <queue>
#include <memory>
#include <format>

using json = nlohmann::json;

namespace Test_Runner {
	struct Result {
		bool Passed;
		std::string Message;
	};

	void assert_node(Suffix_Tree::Node* node, json exp_node) {
		if (!node) {
			throw std::runtime_error("Node is null when expected node is not");
		}

		if (!node->Edge && !exp_node["Edge"].is_null()){
			throw std::runtime_error("Node edge should not be null");
		}
		else if (node->Edge && exp_node["Edge"].is_null()){
			throw std::runtime_error("Node edge should be null");
		}
		else if (!node->Edge && exp_node["Edge"].is_null()) {
			return;
		}

		if (node->Edge->a != exp_node["Edge"][0] || node->Edge->b != exp_node["Edge"][1]) {
			std::string em = std::format("Result Edge {} {} does not equal expected edge {}", node->Edge->a, node->Edge->b, exp_node["Edge"]);
			throw std::runtime_error(em);
		}

		if (node->Child_Nodes.size() != exp_node["Children"].size()) {
			std::string em = std::format("Result children {} doesnt equal expected chilren {}", node->Child_Nodes.size(), exp_node["Children"].size());
			throw std::runtime_error(em);
		}
	}

	void assert_result(Suffix_Tree::Node* res_node, json exp) {
		std::queue<Suffix_Tree::Node*> res_queue;
		std::queue<json> json_queue;

		res_queue.push(res_node);
		json_queue.push(exp["0"]);

		while(!res_queue.empty() && !json_queue.empty()) {
			Suffix_Tree::Node* top = res_queue.front();
			json exp_top = json_queue.front();

			res_queue.pop();
			json_queue.pop();

			assert_node(top, exp_top);

			for (const auto& n: top->Child_Nodes) {
				res_queue.push(n.get());
			}
			
			for (const auto& exp_n: exp_top["Children"]) {
				json_queue.push(exp[std::to_string(exp_n.get<std::uint64_t>())]);
			}
		}

		if (res_queue.empty() != json_queue.empty()) {
			std::string em = std::format("Result queue has {} when expected queue has {}", res_queue.size(), json_queue.size());
			throw std::runtime_error(em);
		}
	}

	Result run_test(json test) {
		std::cout << test["word"] << std::endl;
		std::unique_ptr<Suffix_Tree::Node> result = Suffix_Tree::create(test["word"].get<std::string>());

		Result test_result;
		test_result.Passed = true;
		try {
			if (result.get() == nullptr) {
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
			std::cout << "=============================================" << std::endl;
			std::cout << t_name << std::endl;
			Result res = run_test(t_case);
			if (!res.Passed) {
				std::cout << "RESULT: FAILED" << std::endl;
				std::cout << "REASON: " << res.Message << '\n' << std::endl;
				failed++;
				continue;
			}

			std::cout << "RESULT: PASSED \n" << std::endl;
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
