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

		if (node->Edge->a != exp_node["Edge"][0] || *node->Edge->b != exp_node["Edge"][1]) {
			std::string em = std::format("Result Edge {} {} does not equal expected edge {}", node->Edge->a, *node->Edge->b, exp_node["Edge"]);
			throw std::runtime_error(em);
		}

		if (node->Children.size() != exp_node["Children"].size()) {
			std::string em = std::format("Result children {} doesnt equal expected chilren {}", node->Children.size(), exp_node["Children"].size());
			throw std::runtime_error(em);
		}

		std::cout << "Node is as expected" << std::endl;

	}

	void assert_result(Suffix_Tree::Node* res_node, json exp, std::string word) {
		std::queue<Suffix_Tree::Node*> res_queue;
		std::queue<json> json_queue;

		json_queue.push(exp["0"]);
		res_queue.push(res_node);

		while(!res_queue.empty() && !json_queue.empty()) {
			Suffix_Tree::Node* res_top = res_queue.front();
			res_queue.pop();

			json exp_top = json_queue.front();
			json_queue.pop();

			assert_node(res_top, exp_top);

			for (const auto& id: exp_top["Children"]) {
				std::cout << id << std::endl;
				json exp_node = exp[std::to_string(id.get<std::uint64_t>())];
				std::cout << "2" << std::endl;
				int index = exp_node["Edge"][0].get<std::uint64_t>();

				std::cout << "3" << std::endl;
				res_queue.push(res_top->Children[Suffix_Tree::get_char(word, index)].get());

				std::cout << "4" << std::endl;
				json_queue.push(exp_node);
			}
		}
	}

	Result run_test(json test) {
		std::cout << test["word"] << std::endl;

		Result test_result;
		test_result.Passed = true;
		try {
			std::unique_ptr<Suffix_Tree::Node> result = Suffix_Tree::create(test["word"].get<std::string>());
			if (result.get() == nullptr) {
				throw std::runtime_error("Null pointer returned");
			}
			assert_result(result.get(), test["exp"], test["word"].get<std::string>());
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
