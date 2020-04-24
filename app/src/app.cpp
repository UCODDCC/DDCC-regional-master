#include <signal.h>

#include <regional-balancer/kernel/Server.hpp>
#include <regional-balancer/handlers/mainHandler.hpp>

Server server(atoi(getenv("DDCC_REGIONAL_MASTER_PORT")), mainHandler);

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