#include "json.hpp"
#include <iostream>
#include <fstream>

using json = nlohmann::json;

namespace Test_Runner {
	void load_tests() {
		std::ifstream file(TESTS_PATH);
		json data = json::parse(file);

		std::cout << data["Test_Cases"] << std::endl;

	}

	void run_tests() {

	}
}

int main() {
	std::cout << "Running Tests" << std::endl;
	Test_Runner::load_tests();
	return 0;
}
