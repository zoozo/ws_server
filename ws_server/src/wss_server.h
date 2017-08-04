#ifndef WSS_SERVER_H
#define WSS_SERVER_H

#include "server.h"

namespace zoozo{
class wss_server : public server<wss_config_server>{
    public:
        wss_server(const boost::property_tree::ptree& pt) : server<wss_config_server>(pt){}
        ~wss_server(){};
        void init(uint16_t port);

    private:
        void _on_socket_init(connection_hdl hd1, websocketpp::lib::asio::ssl::stream<websocketpp::lib::asio::ip::tcp::socket> & s);
        std::string _get_password();
        context_ptr _on_tls_init(connection_hdl hdl);
        std::string _password;
};
}
#endif
