#include <shell/shell.hpp>
#include <gtest/gtest.h>

TEST(SHELL, PRINT_HELLO) {
	common::shell::Shell shell{};
	auto result = shell.execute("echo \'some'");
	std::cout << "[OUTPUT] " << result.output;
	// std::cout << "[ERROR] " << result.error << "\n";
	std::cout << "[EXIT CODE] " << result.exit_code << "\n";
	// ASSERT_TRUE(result.output == "some");
	shell.execute("DATA=5");
	result = shell.execute("echo $DATA");
	std::cout << "[OUTPUT] " << result.output;
	// std::cout << "[ERROR] " << result.error << "\n";
	std::cout << "[EXIT CODE] " << result.exit_code << "\n";
	// ASSERT_TRUE(result.output == "5");
}
