#include <chrono>
#include <iostream>
#include <memory>
#include <string>
#include "dep/simple_web_server/server_http.hpp"

using HttpServer = SimpleWeb::Server<SimpleWeb::HTTP>;

int main(int argc, char** argv) {
    if (argc != 2) {
        return -1;
    }

    HttpServer server;
    server.config.port = static_cast<unsigned short>(std::atoi(argv[1]));
    std::cout << "listen: " << server.config.port << std::endl;

    server.resource["^/echo$"]["POST"] =
        [](std::shared_ptr<HttpServer::Response> response,
           std::shared_ptr<HttpServer::Request> request) {
            try {
                // echo
                std::time_t recv_time = std::chrono::system_clock::to_time_t(
                    std::chrono::system_clock::now());
                std::cout << "recv req: " << request->content.string()
                          << ", time: " << std::ctime(&recv_time);
                *response << "HTTP/1.1 200 OK\r\n"
                          << "Content-Length: "
                          << request->content.string().length() << "\r\n\r\n"
                          << request->content.string();
            } catch (const std::exception& e) {
                *response << "HTTP/1.1 400 Bad Request\r\nContent-Length: "
                          << strlen(e.what()) << "\r\n\r\n"
                          << e.what();
            }
        };

    server.start();
}