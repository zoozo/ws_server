#ifndef GENERIC_MODULE_H
#define GENERIC_MODULE_H

#include <map>
#include <vector>
#include <string>
#include <iostream>
#include <boost/shared_ptr.hpp>
#include "../../argument/src/argument.hpp"
#include "../../validation/src/validation.h"
#include <boost/log/trivial.hpp>

namespace zoozo{
#define EXTERN_MODULE(ModuleName)                      \
extern "C" generic_module* create() {                  \
        return new ModuleName;                         \
}                                                      
namespace trivial = boost::log::trivial;
class logger;
class generic_module {
    public:
    generic_module(){}
    virtual ~generic_module(){}

    virtual int run(std::string& output) = 0;

    void load_validation(const std::string& json_file);
    bool validate(const std::string& json_file, const std::string& module, const std::multimap<std::string, std::string>& input);
    const std::string get_validate_error();
    void set_logger(boost::shared_ptr<logger>& logger);
    void logger_write(trivial::severity_level level, const std::string& msg);
    
    protected:
    static boost::shared_ptr<zoozo::validation> _validation_ptr;
    boost::shared_ptr<logger> _log;
    argument args;
    std::string _name;

    private:
};

// the types of the class factories 
typedef generic_module* create_t();

}
#endif 
