#ifndef server_H
#define server_H

#include "ws_config.h"
#include "../../plugin/src/plugin.h"
#include <boost/shared_ptr.hpp>
#include <boost/make_shared.hpp>

namespace zoozo{
#define WS_BROADCAST "WS_BROADCAST"

using websocketpp::connection_hdl;
using websocketpp::lib::mutex;
using websocketpp::lib::unique_lock;
using websocketpp::uri_ptr;

typedef std::map<std::string, std::map<connection_hdl, std::vector<std::string>>> connections;
typedef websocketpp::lib::shared_ptr<websocketpp::lib::asio::ssl::context> context_ptr;
class logger;
template <typename T>
class server{
    public:
        typedef typename T::message_ptr T_message_ptr;
        typedef typename T::connection_ptr T_connection_ptr;
        server(const boost::property_tree::ptree& pt);
        ~server(){}
        void run();


    protected:
        bool _on_validate(connection_hdl hdl);
        void _on_open(connection_hdl hdl);
        void _on_close(connection_hdl hdl);
        void _on_http(connection_hdl hdl);
        void _on_message(connection_hdl hdl, T_message_ptr msg); 
        void _broadcast(const std::vector<std::string>& targets, const std::string& msg);
        void _error_log(websocketpp::log::level channel, std::string const& msg);
        connections _connections;
        mutex    _action_lock;
        T        _server;
        boost::shared_ptr<plugin> _plugin_ptr;
        boost::property_tree::ptree _conf_pt;
        std::ofstream _alog;
        std::ofstream _elog;
        boost::shared_ptr<logger> _lg_ptr;

    private:
};
}
#endif
