#include <signal.h>

#include <lwcpps>
#include <regional-master/handlers/resourceHandler.hpp>
#include <regional-master/configuration.hpp>

LWServer server(resourceHandler, DDCD_REGIONAL_MASTER_PORT);

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