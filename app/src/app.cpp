#include <signal.h>

#include <regional-master/kernel/Server.hpp>
#include <regional-master/handlers/resourceHandler.hpp>
#include <regional-master/configuration.hpp>

Server server(DDCD_REGIONAL_MASTER_PORT, resourceHandler);

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