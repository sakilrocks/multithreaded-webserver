
#include "../include/server.hpp"

int main() {
    WebServer server(8080, "public");
    server.start();
    return 0;
}