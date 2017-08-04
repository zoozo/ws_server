#include "ws_server.h"

namespace zoozo{
void ws_server::init(uint16_t port) {//{{{
    _server.set_socket_init_handler(bind(&ws_server::_on_socket_init, this, ::_1, ::_2));
    // Listen on specified port with extended listen backlog
    //_server.set_listen_backlog(8192);
    _server.listen(port);

    // Start the server accept loop
    _server.start_accept();

}//}}}
void ws_server::_on_socket_init(connection_hdl hd1, boost::asio::ip::tcp::socket & s) {//{{{
    boost::asio::ip::tcp::no_delay option(true);
    s.set_option(option);
}//}}}
}
