#include "process.hpp"

#include <boost/asio.hpp>
#include <boost/process/process.hpp>

#include <boost/process.hpp>

namespace common::shell {

ProcessException::ProcessException(std::string message, unsigned code) : _code(code), _message(std::move(message)) {
    if (_code == 0) { throw std::runtime_error("Well, guest what? 0 means success man"); }
}

const char *ProcessException::what() const noexcept { return this->_message.c_str(); }
} // namespace common::shell
