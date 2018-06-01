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
    std::string json_string =
        "{\"firstName\": \"John\",\"lastName\": \"Smith\",\"age\": 25}";

    for (int i = 0; i < cnt; ++i) {
        client.request("POST", "/json", json_string,
                       [](std::shared_ptr<HttpClient::Response> response,
                          const SimpleWeb::error_code& ec) {
                           if (!ec)
                               std::cout << response->content.rdbuf()
                                         << std::endl;
                       });
    }
    client.io_service->run();
    return 0;
}