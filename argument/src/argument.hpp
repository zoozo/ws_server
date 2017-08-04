#ifndef ARGUMENT_H
#define ARGUMENT_H

#include <string>
#include <map>
#include <vector>
#include <boost/variant.hpp>
#include <stdexcept>

namespace zoozo{

    typedef std::multimap<std::string, boost::variant<int, double, time_t, std::string>> argument_map;
    class argument{
        public:
        argument(){}
        argument(const argument_map& arg_map):_argument(arg_map){}
        void set_argument(const argument_map& arg_map){
            _argument = arg_map;
        }
        int get_count(const std::string& key) const{
            return _argument.count(key);
        }
        template<typename T> T get(const std::string& key) const{
            if(get_count(key) == 0){
                throw std::runtime_error(key + " : not found!!");
            }
            return boost::get<T>(_argument.find(key)->second);
        }
        template<typename T> int get(const std::string& key, std::vector<T>& data) const{
            if(get_count(key) == 0){
                throw std::runtime_error(key + " : not found!!");
            }
            data.clear();
            int count = _argument.count(key);
            auto it = _argument.find(key);
            for(int i = 0; i != count; ++i, ++it){
                data.push_back(boost::get<T>(it->second));
            }
            return count;
        }
        private:
        argument_map _argument;
    };
}

#endif
