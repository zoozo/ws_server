#include <iostream>
#include <dlfcn.h>
#include <stdexcept>
#include <boost/foreach.hpp>
#include "plugin.h"

//#include <set>

namespace zoozo{
plugin::plugin(const std::string& json_file){//{{{
    boost::property_tree::ptree pt;
    boost::property_tree::json_parser::read_json(json_file, pt);

    _load_library(pt.get<std::string>("path"), pt.get_child("modules"));

}//}}}
plugin::~plugin(){//{{{
    for(std::vector<void*>::const_iterator i = _lib_hdls.begin() ; i != _lib_hdls.end() ; i++){
        dlclose(*i);
    }

}//}}}
module_ptr plugin::create(const std::string& library) const{//{{{
    library_map::const_iterator it = _library_map.find(library);
    if(it == _library_map.end()){
        throw std::runtime_error("Cannot find library:" +library);
    }
    return module_ptr(it->second());

}//}}}
bool plugin::check_module_exist(const std::string& library) const{//{{{
    library_map::const_iterator it = _library_map.find(library);
    return it != _library_map.end();
}//}}}

void plugin::_load_library(const std::string& path, const boost::property_tree::ptree& modules){//{{{
    BOOST_FOREACH(const boost::property_tree::ptree::value_type &module, modules){
       _library_map.insert(library_map::value_type(module.second.get<std::string>("name"), _load_library(path + "/" + module.second.get<std::string>("so"))));
    }
}//}}}
create_t* plugin::_load_library(const std::string& library) {//{{{
    void* so = dlopen(library.c_str(), RTLD_LAZY);
    if (!so) {
        std::string err_msg = "Cannot load library: " + library + ":" + dlerror();
        throw std::runtime_error(err_msg);
    }
    _lib_hdls.push_back(so);

    // reset errors
    dlerror();

    // load the symbols
    create_t* create_module = (create_t*) dlsym(so, "create");
    return create_module;

}//}}}
}
