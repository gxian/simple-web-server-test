#include <iostream>
#include <memory>
#include <string>
#include "dep/simple_web_server/client_http.hpp"

using HttpClient = SimpleWeb::Client<SimpleWeb::HTTP>;

int main() {
    HttpClient client("localhost:8080");

    std::string json_string =
        "{\"firstName\": \"John\",\"lastName\": \"Smith\",\"age\": 25}";
    client.request("POST", "/json", json_string,
                   [](std::shared_ptr<HttpClient::Response> response,
                      const SimpleWeb::error_code &ec) {
                       if (!ec)
                           std::cout << response->content.rdbuf() << std::endl;
                   });
    client.io_service->run();
    return 0;
}