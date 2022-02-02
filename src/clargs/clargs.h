#ifndef CLARGS_H
#define CLARGS_H

#include <vector>
#include <string>

class CLArgsParser {
    public:
        CLArgsParser(int argc, const char* const* argv);
        bool option_exists(const std::string &option) const;
        const std::string& get_parameter(const std::string &option) const;
    private:
        std::vector<std::string> tokens;
};

#endif