#pragma once

#include <string>
#include <sys/ioctl.h>
#include <unistd.h>

namespace cli {

void printCentered(const std::string &);

void clear();
void printLogo();

} // namespace cli
