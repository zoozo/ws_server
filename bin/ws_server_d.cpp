#include "../ws_server/src/ws_server.h"
#include "../ws_server/src/wss_server.h"

using namespace std;
using namespace zoozo;

int main(int argc, char * argv[]) {
    // Create a server endpoint

    if (argc != 2) {
        cout<<"please input json conf!!"<<endl;
        return 0;
    }

    boost::property_tree::ptree pt;
    short port;
    size_t num_of_thread;
    short using_tls;
    try{
        boost::property_tree::json_parser::read_json(argv[1], pt);
        port = pt.get<int>("port");
        num_of_thread = pt.get<int>("threads");
        using_tls = pt.get<int>("using_tls");

        pt.get<std::string>("modules_json");
        pt.get<std::string>("validate_json");
        pt.get<std::string>("module_log");
        pt.get<std::string>("access_log");
        pt.get<std::string>("error_log");

        if(using_tls == 1){
            pt.get<std::string>("tls_cert");
            pt.get<std::string>("tls_key");
        }
    }
    catch(exception& e){
        cout<<"configure error:"<<e.what()<<endl;
        return 1;
    }

    cout<<"port:"<<port<<endl;
    cout<<"num of thread:"<<num_of_thread<<endl;
    cout<<"using_tls:"<<using_tls<<endl;

    if(using_tls == 1){
        try {
            wss_server server(pt);
            server.init(port);

            // Start the ASIO io_service run loop
            if (num_of_thread == 1) {
                server.run();
            } else {
                typedef websocketpp::lib::shared_ptr<websocketpp::lib::thread> thread_ptr;
                vector<thread_ptr> ts;
                for (size_t i = 0; i < num_of_thread; i++) {
                    ts.push_back(websocketpp::lib::make_shared<websocketpp::lib::thread>(bind(&wss_server::run, &server)));
                }

                for (size_t i = 0; i < num_of_thread; i++) {
                    ts[i]->join();
                }
            }

        } catch (std::exception const & e) {
            cout << "configure error: " << e.what() << endl;
            return 1;
        }
    }
    else{
        try {
            ws_server server(pt);
            server.init(port);

            // Start the ASIO io_service run loop
            if (num_of_thread == 1) {
                server.run();
            } else {
                typedef websocketpp::lib::shared_ptr<websocketpp::lib::thread> thread_ptr;
                vector<thread_ptr> ts;
                for (size_t i = 0; i < num_of_thread; i++) {
                    ts.push_back(websocketpp::lib::make_shared<websocketpp::lib::thread>(bind(&ws_server::run, &server)));
                }

                for (size_t i = 0; i < num_of_thread; i++) {
                    ts[i]->join();
                }
            }

        } catch (std::exception const & e) {
            cout << "configure error: " << e.what() << endl;
            return 1;
        }
    }
}
