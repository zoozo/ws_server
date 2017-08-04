#include "validation.h"
#include <iostream>
#include <boost/property_tree/ptree.hpp>
#include <boost/property_tree/json_parser.hpp>
#include <boost/foreach.hpp>
#include <boost/lexical_cast.hpp>
#include <boost/algorithm/string/join.hpp>
#include <exception>

namespace zoozo{
    validation::validation(const std::string& json_conf){//{{{
        boost::property_tree::ptree pt;
        boost::property_tree::json_parser::read_json(json_conf, pt);

        std::string module_name, name, type, required, min, max;

        BOOST_FOREACH(const boost::property_tree::ptree::value_type &module, pt){
            module_name = module.first;
            std::vector<std::string> requireds;
            //std::cout<<"name:"<<module_name<<std::endl;

            std::map<std::string, std::map<std::string, std::string>> config_map;
            BOOST_FOREACH(const boost::property_tree::ptree::value_type &config, pt.get_child(module_name)){
                std::map<std::string, std::string> module_map;
                name = config.second.get<std::string>("name");
                type = config.second.get<std::string>("type");
                required = config.second.get<std::string>("required");
                if(config.second.find("minimum") != config.second.not_found()){
                    min = config.second.get<std::string>("minimum");
                    module_map.insert(std::map<std::string, std::string>::value_type("minimum", min));
                }
                if(config.second.find("maximum") != config.second.not_found()){
                    max = config.second.get<std::string>("maximum");
                    module_map.insert(std::map<std::string, std::string>::value_type("maximum", max));
                }

                module_map.insert(std::map<std::string, std::string>::value_type("type", type));
                module_map.insert(std::map<std::string, std::string>::value_type("required", required));
                config_map.insert(std::map<std::string, std::map<std::string, std::string>>::value_type(name, module_map));
                if(required == "required"){
                    requireds.push_back(name);
                }
            }
            _required_keys.insert(std::map<std::string, std::vector<std::string>>::value_type(module_name, requireds));
            _validation.insert(validation_map::value_type(module_name, config_map));
        }
    }//}}} 
    bool validation::validate(const std::string& module, const std::multimap<std::string, std::string>& input, argument& args){//{{{
        _error_message.clear();
        std::map<std::string, std::map<std::string, std::string>> rules = _validation[module];
        std::vector<std::string> required_keys = _required_keys[module];

        argument_map arg_map;
        std::string type;
        bool result = true;

        BOOST_FOREACH(auto pair, input){
            if(rules.find(pair.first) == rules.end()){
                continue;
            }
            //std::cout<<pair.first<<":"<<pair.second<<":"<<rules[pair.first]["type"]<<":"<<rules[pair.first]["required"]<<std::endl;
            type = rules[pair.first]["type"];
            try{
                if(type == "int"){
                    int value = boost::lexical_cast<int>(pair.second);
                    if(rules[pair.first].find("minimum") != rules[pair.first].end()){
                        int min = boost::lexical_cast<int>(rules[pair.first]["minimum"]);
                        if(value < min){
                            _error_message.push_back(pair.first + ": minimum:" + rules[pair.first]["minimum"]);
                            result = false;
                        }
                    }
                    if(rules[pair.first].find("maximum") != rules[pair.first].end()){
                        int max = boost::lexical_cast<int>(rules[pair.first]["maximum"]);
                        if(value > max){
                            _error_message.push_back(pair.first + ": maximum:" + rules[pair.first]["maximum"]);
                            result = false;
                        }
                    }
                    arg_map.insert(argument_map::value_type(pair.first, value));
                }
                else if(type == "time_t"){
                    arg_map.insert(argument_map::value_type(pair.first, boost::lexical_cast<time_t>(pair.second)));
                }
                else if(type == "double"){
                    double value = boost::lexical_cast<double>(pair.second);
                    if(rules[pair.first].find("minimum") != rules[pair.first].end()){
                        double min = boost::lexical_cast<double>(rules[pair.first]["minimum"]);
                        if(value < min){
                            _error_message.push_back(pair.first + ": minimum:" + rules[pair.first]["minimum"]);
                            result = false;
                        }
                    }
                    if(rules[pair.first].find("maximum") != rules[pair.first].end()){
                        double max = boost::lexical_cast<double>(rules[pair.first]["maximum"]);
                        if(value > max){
                            _error_message.push_back(pair.first + ": maximum:" + rules[pair.first]["maximum"]);
                            result = false;
                        }
                    }
                    arg_map.insert(argument_map::value_type(pair.first, value));
                }
                else if(type == "string"){
                    int value = pair.second.size();
                    if(rules[pair.first].find("minimum") != rules[pair.first].end()){
                        int min = boost::lexical_cast<int>(rules[pair.first]["minimum"]);
                        if(value < min){
                            _error_message.push_back(pair.first + ": minimum:" + rules[pair.first]["minimum"]);
                            result = false;
                        }
                    }
                    if(rules[pair.first].find("maximum") != rules[pair.first].end()){
                        int max = boost::lexical_cast<int>(rules[pair.first]["maximum"]);
                        if(value > max){
                            _error_message.push_back(pair.first + ": maximum:" + rules[pair.first]["maximum"]);
                            result = false;
                        }
                    }
                    arg_map.insert(argument_map::value_type(pair.first, pair.second));
                }
                else{    
                    _error_message.push_back(pair.first + ":unknow type");
                    result = false;
                }
            }
            catch(std::exception& e){
                _error_message.push_back(pair.first + ":" + e.what());
                result = false;
            }
        }

        BOOST_FOREACH(auto key, required_keys){
            if(input.find(key) == input.end()){
                _error_message.push_back(key + ":required");
                result = false;
            }
        }
        if(result){
            args.set_argument(arg_map);
        }

        return result;
    }//}}}
    const std::string validation::get_error_message() const{//{{{
        return boost::algorithm::join(_error_message, ",");
    }//}}}
}
