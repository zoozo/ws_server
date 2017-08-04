#ifndef ws_server_H
#define ws_server_H

#include "server.h"

namespace zoozo{
class ws_server : public server<ws_config_server>{
    public:
        ws_server(const boost::property_tree::ptree& pt) : server<ws_config_server>(pt){}
        ~ws_server(){};
        void init(uint16_t port);

    private:
        void _on_socket_init(connection_hdl hd1, websocketpp::lib::asio::ip::tcp::socket & s);
};
}
#endif
