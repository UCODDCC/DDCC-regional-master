#include <iostream>
#include <regional-balancer/kernel/Server.hpp>

std::string serverHandlerOrchestrator(std::string payload){
    return std::string("hello from server! <").append(payload).append(">");
}

int main() {
    printf("test");
    Server server(7707, serverHandlerOrchestrator);
    for(;;) server.handleNextConnection();
}