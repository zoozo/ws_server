#ifndef PLUGIN_H
#define PLUGIN_H

#include <vector>
#include <boost/shared_ptr.hpp>
#include <boost/property_tree/ptree.hpp>
#include <boost/property_tree/json_parser.hpp>
#include "../../generic_module/src/generic_module.h"

namespace zoozo{
typedef std::map<std::string, create_t*> library_map;
typedef boost::shared_ptr<generic_module> module_ptr;

class plugin {
    public:
    plugin(const std::string& json_file);
    ~plugin();
    module_ptr create(const std::string& name) const;
    bool check_module_exist(const std::string& name) const;

    private:
    void _load_library(const std::string& path, const boost::property_tree::ptree& modules);
    create_t* _load_library(const std::string& library);

    library_map        _library_map;
    std::vector<void*> _lib_hdls;


};
}
#endif 
