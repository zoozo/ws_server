#ifndef WS_UTIL_H
#define WS_UTIL_H

#include <boost/tokenizer.hpp>
#include <map>
#include <string>

namespace zoozo{

typedef std::multimap<std::string, std::string> request;
class ws_util{
    public:
    static std::string get_url_path(const std::string& url);
    static std::string get_url_action(const std::string& url);
    static std::string get_url_query(const std::string& url);

    
    static std::string get_return_json(const int code, const std::string& msg);
    static bool url_decode(const std::string& in, std::string& out);
    static int get_url_argument(const std::string& url, request& args);
    static int get_argument(const std::string& message, request& args);
};
}
#endif
