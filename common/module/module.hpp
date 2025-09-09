// std::cout << "Loading a module\n";
//
// void* module = dlopen("./example/module/build/libmodule.so", RTLD_LAZY);
// if (!module) {
// 	std::cerr << dlerror() << "\n";
// 	exit(1);
// }
// dlerror();
// void (*printer)(const std::string&) = reinterpret_cast<void(*)(const std::string&)>(dlsym(module, "print"));
// printer("printing data with module function");
// std::cout << "Finished execution\n";
//
// dlclose(module);
//

#pragma once

namespace module {

// placholder for now
class Module {};
} // namespace module
