#ifndef VALIDATION_H
#define VALIDATION_H

#include <string>
#include <vector>
#include <map>
#include "../../argument/src/argument.hpp"

namespace zoozo{

typedef std::map<std::string, std::map<std::string, std::map<std::string, std::string>>> validation_map;
class validation{
    public:
        validation(const std::string& json);
        bool validate(const std::string& module, const std::multimap<std::string, std::string>& input, argument& args);
        const std::string get_error_message() const;
    private:
        validation_map _validation;
        std::map<std::string, std::vector<std::string>> _required_keys;
        std::vector<std::string> _error_message;
};
}

#endif
