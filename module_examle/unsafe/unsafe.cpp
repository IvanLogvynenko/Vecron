#include <iostream>
#include <string>

extern "C" void unsafe_print(const std::string& input) {
	std::cout << "Unsafe module output: " << input << "\n";
}
