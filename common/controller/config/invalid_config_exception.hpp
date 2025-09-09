#include <exception>
#include <string>
#include <utility>
namespace config {

class InvalidConfig : public std::exception {
private: 
	std::string _msg;
public:
	explicit InvalidConfig(std::string msg) : _msg(std::move(msg)) {}
	const char * what() const noexcept override {
		return std::string("Syntax error: ").append(_msg).c_str();
	}
};

} // namespace config
