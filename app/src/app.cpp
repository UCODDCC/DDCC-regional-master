#include <signal.h>
#include <regional-balancer/kernel/Server.hpp>


std::string serverHandlerOrchestrator(std::string payload){
    std::string response = "+hello from server!<";
    response.append("response here");
    response.append(">");
    return response;
}


Server server(7654, serverHandlerOrchestrator);

void sigHandler(int signum);


int main() {
    signal(SIGINT, sigHandler);
    signal(SIGTERM, sigHandler);
    signal(SIGABRT, sigHandler);
    while(true) server.handleNextConnection();
}

void sigHandler (int signum){
    server.exit();
}