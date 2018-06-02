#include <iostream>
#include <memory>
#include <string>
#include "dep/simple_web_server/client_http.hpp"

using HttpClient = SimpleWeb::Client<SimpleWeb::HTTP>;

int main(int argc, char** argv) {
    if (argc != 4) {
        return -1;
    }
    std::string ip, port, count;
    ip = argv[1];
    port = argv[2];
    count = argv[3];
    std::string address = ip + ":" + port;
    int cnt = std::atoi(count.c_str());

    HttpClient client(address);
    std::string head = "echo ";

    for (int i = 0; i < cnt; ++i) {
        std::string s = head + std::to_string(i);
        std::time_t send_time = std::chrono::system_clock::to_time_t(
            std::chrono::system_clock::now());
        std::cout << "send req:" << s << ", time: " << std::ctime(&send_time);
        client.request("POST", "/echo", s,
                       [](std::shared_ptr<HttpClient::Response> response,
                          const SimpleWeb::error_code& ec) {
                           if (!ec) {
                               std::cout << response->content.rdbuf()
                                         << std::endl;
                           } else {
                               std::cerr << ec.message().c_str() << std::endl;
                           }
                       });
    }
    client.io_service->run();
    return 0;
}