#include <iostream>
#include <string>

extern "C" void print(const std::string& data) {
	std::cout << data << "\n";
}
