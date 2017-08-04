#include "server.h"
#include "ws_util.h"
#include <boost/algorithm/string/split.hpp>
#include <boost/algorithm/string/classification.hpp>
#include <boost/foreach.hpp>
#include <iostream>
#include <fstream>
#include <boost/log/trivial.hpp>
#include "../../logger/src/logger.h"

namespace zoozo{
template<typename T> server<T>::server(const boost::property_tree::ptree& pt) : _conf_pt(pt) {//{{{
//    try{
        _alog.open(pt.get<std::string>("access_log"), std::ofstream::out | std::ofstream::app);
        _elog.open(pt.get<std::string>("error_log"), std::ofstream::out | std::ofstream::app);
        _server.get_alog().set_ostream(&_alog);
        _server.get_elog().set_ostream(&_elog);
        std::string modules_json = pt.get<std::string>("modules_json");
        _plugin_ptr = boost::make_shared<plugin>(modules_json);
        _lg_ptr = boost::make_shared<logger>(pt.get<std::string>("module_log"));

        //_server.clear_access_channels(websocketpp::log::alevel::devel);
        //_server.clear_error_channels(websocketpp::log::alevel::all);
        //_server.set_access_channels(websocketpp::log::alevel::all | websocketpp::log::alevel::devel);
        //_server.set_error_channels(websocketpp::log::alevel::connect);
        // Initialize Asio Transport
//    }catch(coVnst std::exception & e) {
//        throw 
//    }

    try{
        _server.init_asio();
        _server.set_reuse_addr(true);

        // Register handler callbacks
        _server.set_open_handler(bind(&server::_on_open,this,::_1));
        _server.set_close_handler(bind(&server::_on_close,this,::_1));
        _server.set_http_handler(bind(&server::_on_http,this,::_1));
        _server.set_validate_handler(bind(&server::_on_validate,this,::_1));
        _server.set_message_handler(bind(&server::_on_message,this,::_1, ::_2));
    } catch (const std::exception & e) {
        _error_log(websocketpp::log::alevel::app, e.what());
        throw std::runtime_error(e.what());
    }
}//}}}
template<typename T> void server<T>::run() {//{{{
    // Start the ASIO io_service run loop
    try {
        _server.run();
    } catch (const std::exception & e) {
        _error_log(websocketpp::log::alevel::app, e.what());
    }
}//}}}

template<typename T> bool server<T>::_on_validate(connection_hdl hdl) {//{{{
    T_connection_ptr conn = _server.get_con_from_hdl(hdl);
    bool ret = _plugin_ptr->check_module_exist(ws_util::get_url_action(conn->get_resource()));
    return ret;

    
}//}}}
template<typename T> void server<T>::_on_open(connection_hdl hdl) {//{{{
    T_connection_ptr conn = _server.get_con_from_hdl(hdl);
    request args;
    std::string action = ws_util::get_url_action(conn->get_resource());
    int count = ws_util::get_url_argument(conn->get_resource(), args);

    if(count){
        request::iterator it = args.find(WS_BROADCAST);
        if(it != args.end()){
            std::vector<std::string> handler;
            boost::split(handler, it->second, boost::is_any_of(","));
            unique_lock<mutex> lock(_action_lock);
            _connections[action][hdl] = handler;
            lock.unlock();
        }
    }
}//}}}
template<typename T> void server<T>::_on_close(connection_hdl hdl) {//{{{
    T_connection_ptr conn = _server.get_con_from_hdl(hdl);
    std::string action = ws_util::get_url_action(conn->get_resource());
    unique_lock<mutex> lock(_action_lock);
    _connections[action].erase(hdl);
    lock.unlock();
}//}}}
template<typename T> void server<T>::_on_message(connection_hdl hdl, T_message_ptr msg) {//{{{
    T_connection_ptr conn = _server.get_con_from_hdl(hdl);

    request args;
    std::string output;
    std::string message = msg->get_payload();
    ws_util::get_argument(message, args);
    std::string action = ws_util::get_url_action(conn->get_resource());
    module_ptr m_ptr = _plugin_ptr->create(action);
    try{
        if(!m_ptr->validate(_conf_pt.get<std::string>("validate_json"), action, args)){
            output = m_ptr->get_validate_error();
            _server.send(hdl, ws_util::get_return_json(400, output), websocketpp::frame::opcode::text);
            return;
        }
        m_ptr->set_logger(_lg_ptr);
        int code = m_ptr->run(output);
        if(_connections[action].find(hdl) != _connections[action].end()){
            _broadcast(_connections[action][hdl], ws_util::get_return_json(code, output));
        }
        else{
            _server.send(hdl, ws_util::get_return_json(code, output), websocketpp::frame::opcode::text);
        }
    }
    catch(std::exception& e){
        _error_log(websocketpp::log::alevel::app, e.what());
        _server.send(hdl, ws_util::get_return_json(500, std::string(e.what())), websocketpp::frame::opcode::text);
        return;
    }

}//}}}
template<typename T> void server<T>::_on_http(connection_hdl hdl) {//{{{
    T_connection_ptr conn = _server.get_con_from_hdl(hdl);
    //std::cout<<"request body:"<<conn->get_request_body()<<std::endl;

    std::string resource;
    ws_util::url_decode(conn->get_resource(), resource);
    std::string action = ws_util::get_url_action(resource);
    //std::cout<<"action:"<<action<<std::endl;
    if(!_plugin_ptr->check_module_exist(action)){
        conn->set_status(websocketpp::http::status_code::not_found);
        conn->set_body("page not found");
        return;
    }
    request args;
    std::string output;
    int count = ws_util::get_url_argument(resource, args);
    module_ptr m_ptr = _plugin_ptr->create(ws_util::get_url_action(resource));
    try{
        if(!m_ptr->validate(_conf_pt.get<std::string>("validate_json"), action, args)){
            conn->set_status(websocketpp::http::status_code::bad_request);
            conn->set_body(m_ptr->get_validate_error());

            return;
        }
        m_ptr->set_logger(_lg_ptr);
        int code = m_ptr->run(output);
        std::string result = ws_util::get_return_json(code, output);

        if(count){
            request::iterator it = args.find(WS_BROADCAST);
            if(it != args.end()){
                std::vector<std::string> handler;
                boost::split(handler, it->second, boost::is_any_of(","));
                _broadcast(handler, result);
            }
        }
        conn->set_status(websocketpp::http::status_code::ok);

        conn->set_body(result);
    }
    catch(std::exception& e){
        _error_log(websocketpp::log::alevel::app, e.what());
        conn->set_status(websocketpp::http::status_code::internal_server_error);
        conn->set_body(e.what());
    }
}//}}}
template<typename T> void server<T>::_broadcast(const std::vector<std::string>& targets, const std::string& msg){//{{{
    unique_lock<mutex> lock(_action_lock);

    BOOST_FOREACH(auto target, targets){
        BOOST_FOREACH(auto connection, _connections[target]){
            _server.send(connection.first, msg, websocketpp::frame::opcode::text);
        }
    }
    lock.unlock();
}//}}}
template<typename T> void server<T>::_error_log(websocketpp::log::level channel, std::string const & msg) {//{{{
    _server.get_alog().write(channel, msg);
}//}}}

//http://stackoverflow.com/questions/495021/why-can-templates-only-be-implemented-in-the-header-file
template class server<ws_config_server>;
template class server<wss_config_server>;
}
