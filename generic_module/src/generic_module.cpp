#include "generic_module.h"
#include <boost/make_shared.hpp>
#include "../../../logger/src/logger.h"

namespace zoozo{
void generic_module::load_validation(const std::string& json_file){//{{{
    if(!_validation_ptr){
        _validation_ptr = boost::make_shared<zoozo::validation>(json_file);
    }
}//}}}
bool generic_module::validate(const std::string& json_file, const std::string& module, const std::multimap<std::string, std::string>& input){//{{{
    _name = module;
    load_validation(json_file);
    if(!_validation_ptr){
        //throw error;
    }
    return _validation_ptr->validate(module, input, args);
}//}}}
const std::string generic_module::get_validate_error(){//{{{
    return _validation_ptr->get_error_message();
}//}}}
    void generic_module::set_logger(boost::shared_ptr<logger>& logger){//{{{
        _log = logger;
    }//}}}
    void generic_module::logger_write(trivial::severity_level level, const std::string& msg){//{{{
        _log->write(level, "[" + _name + "] " + msg);
    }//}}}

boost::shared_ptr<zoozo::validation> generic_module::_validation_ptr;
}
