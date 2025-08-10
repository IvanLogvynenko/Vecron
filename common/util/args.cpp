#include "args.hpp"
#include <functional>
#include <unordered_map>

std::pair<std::map<std::string, std::string>, std::vector<std::string>>
util::parse_args(const std::vector<std::string> &args) {
    std::map<std::string, std::string> parsedArgs = {};
    std::vector<std::string> rest = {};

    // efficient switch case on strings
    static const std::unordered_map<std::string,
                                    std::function<void(const std::string &)>>
        argMap = {
            {"-c",
             [&](const std::string &value) {
                 parsedArgs["configPath"] = value;
             }},
            {"-t",
             [&](const std::string &value) {
                 parsedArgs["targetPath"] = value;
             }},
            {"--vars",
             [&](const std::string &value) { parsedArgs["vars"] = value; }},
            // {"-c", [&](const std::string& value) { parsedArgs["configPath"] = value; }},
        };

    for (size_t i = 0; i < args.size(); i++) {
        auto it = argMap.find(args[i]);
        if (it != argMap.end()) {
            it->second(args[++i]);
        } else {
            rest.push_back(args[i]);
        }
    }

    return {parsedArgs, rest};
}
