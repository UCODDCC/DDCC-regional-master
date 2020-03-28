#ifndef _REGIONAL_MASTER_KERNEL_SERVER_
#define _REGIONAL_MASTER_KERNEL_SERVER_

#include <string>
#include <vector>
#include <sys/types.h>
#include <sys/socket.h>
#include <netinet/in.h>
#include <netdb.h>
#include <unistd.h>
#include <arpa/inet.h>
#include <cstring>
#include <stdexcept>
#include <thread>

#include <regional-balancer/configuration.hpp>


/**
 * All the handlers must follow this type
 */
typedef std::string (*handlerType)(const std::string&);

struct serverConnection {
    int socket_fd = -1;
    struct sockaddr client_sock_addr{};
    socklen_t len{};
};

void handleNextConnectionThreaded(handlerType handler, serverConnection client);

/**
 * A connection oriented with client sessions
 * The client session only saves the connection itself, but the rest is STATELESS, no user cookie, or any other kind
 * of data.
 * This server does not handle any kind of user validation, that is why the handler is present, the idea for this
 * class is to be as modular as it can be.
 */
class Server {

private:
    int server_fd_;
    sockaddr_in server_sock_addr_{};
    int connectionCap_;
    std::vector<std::thread> threads_;

public:
    handlerType handler_;
    Server(int portno, handlerType requestHandler);
    int getConnectionCap() const;
    void setConnectionCap(int cap);
    int getNumberOfConnections() const;

    void handleNextConnection();

    void exit();
};

#endif
