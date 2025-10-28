
#include "../include/server.hpp"

#include <iostream>
#include <thread>
#include <fstream>
#include <sstream>
#include <vector>
#include <cstring>
#include <unistd.h>
#include <arpa/inet.h>

WebServer::WebServer(int port, const std::string& rootDir)
    : port(port), rootDir(rootDir) {}

void WebServer::start() {
    int server_fd = socket(AF_INET, SOCK_STREAM, 0);
    if (server_fd == -1) {
        perror("socket creation failed");
        return;
    }

    sockaddr_in address{};
    address.sin_family = AF_INET;
    address.sin_addr.s_addr = INADDR_ANY;
    address.sin_port = htons(port);

    if (bind(server_fd, (struct sockaddr*)&address, sizeof(address)) < 0) {
        perror("bind failed");
        close(server_fd);
        return;
    }

    if (listen(server_fd, 10) < 0) {
        perror("listen failed");
        close(server_fd);
        return;
    }

    std::cout << "server running on http://localhost:" << port << std::endl;

    while (true) {
        int clientSocket = accept(server_fd, nullptr, nullptr);
        if (clientSocket < 0) {
            perror("accept failed");
            continue;
        }

        std::thread(&WebServer::handleClient, this, clientSocket).detach();
    }
}

void WebServer::handleClient(int clientSocket) {
    char buffer[4096];
    int bytesRead = read(clientSocket, buffer, sizeof(buffer) - 1);
    if (bytesRead <= 0) {
        close(clientSocket);
        return;
    }

    buffer[bytesRead] = '\0';
    std::string request(buffer);

    std::istringstream requestStream(request);
    std::string method, path;
    requestStream >> method >> path;

    if (path == "/") path = "/index.html";

    std::string filePath = rootDir + path;
    std::string response = buildHttpResponse(filePath);

    send(clientSocket, response.c_str(), response.size(), 0);
    close(clientSocket);
}

std::string WebServer::buildHttpResponse(const std::string& filePath) {
    std::ifstream file(filePath, std::ios::binary);
    std::ostringstream response;

    if (!file) {
        response << "HTTP/1.1 404 Not Found\r\n"
                 << "Content Type: text/html\r\n\r\n"
                 << "<h1>404 Not Found</h1>";
        return response.str();
    }

    std::stringstream buffer;
    buffer << file.rdbuf();
    std::string content = buffer.str();

    response << "HTTP/1.1 200 OK\r\n"
             << "Content Type: text/html\r\n"
             << "Content Length: " << content.size() << "\r\n\r\n"
             << content;

    return response.str();
}