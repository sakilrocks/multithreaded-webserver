
#ifndef SERVER_HPP
#define SERVER_HPP

#include <string>

class WebServer {
public:
    WebServer(int port, const std::string& rootDir);
    void start();

private:
    int port;
    std::string rootDir;

    void handleClient(int clientSocket);
    std::string buildHttpResponse(const std::string& filePath);
};


#endif