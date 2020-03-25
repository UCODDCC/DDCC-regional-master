#include <signal.h>

#include <regional-balancer/kernel/Server.hpp>
#include <regional-balancer/handlers/mainHandler.hpp>



Server server(7654, mainHandler);

void sigHandler(int signum);


int main() {
    signal(SIGINT, sigHandler);
    signal(SIGTERM, sigHandler);
    signal(SIGABRT, sigHandler);
    server.handleNextConnection();
    server.handleNextConnection();
    server.exit();
}

void sigHandler (int signum){
    server.exit();
}