#include <signal.h>

#include <regional-balancer/kernel/Server.hpp>
#include <regional-balancer/handlers/mainHandler.hpp>
#include <regional-balancer/configuration.hpp>


Server server(DDCD_REGIONAL_MASTER_PORT, mainHandler);

void sigHandler(int signum);


int main() {
    signal(SIGINT, sigHandler);
    signal(SIGTERM, sigHandler);
    signal(SIGABRT, sigHandler);
    while (true) server.handleNextConnection();
}

void sigHandler (int signum){
    server.exit();
}