#include "wss_server.h"

namespace zoozo{
void wss_server::init(uint16_t port) {//{{{
    /*
    _server.clear_access_channels(websocketpp::log::alevel::all);
    _server.clear_error_channels(websocketpp::log::alevel::all);
    // Initialize Asio Transport
    _server.init_asio();
    _server.set_reuse_addr(true);

    // Register handler callbacks
    _server.set_open_handler(bind(&wss_server::_on_open,this,::_1));
    _server.set_close_handler(bind(&wss_server::_on_close,this,::_1));
    _server.set_http_handler(bind(&wss_server::_on_http,this,::_1));
    _server.set_message_handler(bind(&wss_server::_on_message,this,::_1,::_2));
    */
    _server.set_socket_init_handler(bind(&wss_server::_on_socket_init, this, ::_1, ::_2));
    _server.set_tls_init_handler(bind(&wss_server::_on_tls_init,this,::_1));
    // Listen on specified port with extended listen backlog
    //_server.set_listen_backlog(8192);
    _server.listen(port);

    // Start the server accept loop
    _server.start_accept();

}//}}}
void wss_server::_on_socket_init(connection_hdl hd1, websocketpp::lib::asio::ssl::stream<websocketpp::lib::asio::ip::tcp::socket>& s) {//{{{
    boost::asio::ip::tcp::no_delay option(true);
    s.lowest_layer().set_option(option);
}//}}}
std::string wss_server::_get_password() {//{{{
    if(_password.size() == 0){
        std::ifstream file(_conf_pt.get<std::string>("tls_key"));
        std::getline(file, _password);
    }
    return _password;


}//}}}
context_ptr wss_server::_on_tls_init(connection_hdl hdl) {//{{{
    context_ptr ctx(new boost::asio::ssl::context(boost::asio::ssl::context::tlsv1));

    try {
        ctx->set_options(boost::asio::ssl::context::default_workarounds |
                boost::asio::ssl::context::no_sslv2 |
                boost::asio::ssl::context::no_sslv3 |
                boost::asio::ssl::context::single_dh_use);
        ctx->set_password_callback(bind(&wss_server::_get_password, this));
        ctx->use_certificate_chain_file(_conf_pt.get<std::string>("tls_cert"));
        ctx->use_private_key_file(_conf_pt.get<std::string>("tls_cert"), boost::asio::ssl::context::pem);
    } catch (std::exception& e) {
        _error_log(websocketpp::log::alevel::app, e.what());
    }
    return ctx;

}//}}}
}
