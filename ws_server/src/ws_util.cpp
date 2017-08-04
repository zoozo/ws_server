#include <boost/tokenizer.hpp>
#include "ws_util.h"
#include <iostream>
#include<sstream>
#include <boost/property_tree/ptree.hpp>
#include <boost/property_tree/json_parser.hpp>

namespace zoozo{
    std::string ws_util::get_url_path(const std::string& url){//{{{
        std::size_t found = url.find('?');
        if (found != std::string::npos) {
            return url.substr(0, found);
        } else {
            return "";
        }
    }//}}}
    std::string ws_util::get_url_action(const std::string& url){//{{{
        std::size_t found = url.find('?');
        if (found != std::string::npos) {
            return url.substr(1, found - 1);
        } else {
            return url.substr(1);
        }
    }//}}}
    std::string ws_util::get_url_query(const std::string& url){//{{{
        std::size_t found = url.find('?');
        if (found != std::string::npos) {
            return url.substr(found + 1);
        } else {
            return "";
        }
    }//}}}
    
    int ws_util::get_url_argument(const std::string& url, request& args){//{{{
        std::string query = get_url_query(url);
        if(query.size() == 0) return 0;

        return get_argument(query, args);
    }//}}}
    int ws_util::get_argument(const std::string& message, request& args){//{{{
        boost::char_separator<char> sep("&");
        boost::tokenizer<boost::char_separator<char> > tokens(message, sep);

        for (boost::tokenizer<boost::char_separator<char> >::iterator tok_iter = tokens.begin();
                tok_iter != tokens.end(); ++tok_iter){
            if((*tok_iter).length() > 0){
                size_t pos = (*tok_iter).find('=');
                //std::cout<<(*tok_iter).substr(0, pos)<<":"<<(*tok_iter).substr(pos + 1)<<std::endl;
                args.insert(request::value_type((*tok_iter).substr(0, pos), (*tok_iter).substr(pos + 1)));
            }
        }

        return args.size();
    }//}}}
    bool ws_util::url_decode(const std::string& in, std::string& out) {//{{{
        out.clear();
        out.reserve(in.size());
        for (std::size_t i = 0; i < in.size(); ++i)
        {
            if (in[i] == '%')
            {
                if (i + 3 <= in.size())
                {
                    int value = 0;
                    std::string str = in.substr(i + 1, 2);
                    std::istringstream is(in.substr(i + 1, 2));
                    if (is >> std::hex >> value)
                    {
                        out += static_cast<char>(value);
                        i += 2;
                    }
                    else
                    {
                        return false;
                    }
                }
                else
                {
                    return false;
                }
            }
            else if (in[i] == '+')
            {
                out += ' ';
            }
            else
            {
                out += in[i];
            }
        }
        return true;
    }//}}}
    std::string ws_util::get_return_json(const int code, const std::string& msg){//{{{
        std::ostringstream output;
        std::stringstream message;

        message << msg;

        boost::property_tree::ptree pt;
        boost::property_tree::ptree msg_pt;
        pt.put("code", code);
        try{
            boost::property_tree::read_json(message, msg_pt);
            pt.add_child("output", msg_pt);
        }
        catch(std::exception& e){
            pt.put("output", msg);
        }
        write_json(output, pt);

        return output.str();
    }//}}}
}
