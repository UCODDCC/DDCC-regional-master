#ifndef _REGIONAL_MASTER_KERNEL_CLIENT_
#define _REGIONAL_MASTER_KERNEL_CLIENT_

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
#include <pthread.h>
#include <time.h>

#include <regional-balancer/configuration.hpp>

/**
 * This struct holds the necessary parameters for the listenThread function
 * the server socket and a pointer to the future server message
 */
struct listenThreadParams {
    int socket;
    std::string* payload;
};

/**
 * Threaded function for listening to the server
 * @param params listenThreadParams struct
 * @return nothing
 */
void* listenThread(void* params);

/**
 * This simple TCP client to send and receive data from a TCP server
 * This server implements listen timeout, so it makes use of the pthread lib
 */
class Client {
private:
    int socket_fd_;
    sockaddr_in server_dir_{};
    socklen_t server_dir_len_;
public:
    /**
     * Class constructor
     * @param addr ipv4 address of the server
     * @param portno server port
     */
    Client(const std::string& addr, int portno);

    /**
     * Message sender
     * @param payload the message that will be send to the server
     * @return error code, same as the send function
     */
    int sendMessage(const std::string& payload);

    /**
     * Timeout enable listen function
     * @param timeout time in seconds
     * @return server payload
     */
    std::string listen(int timeout = 60);

    /**
     * sends a exit message and closes the socket
     * @return error code, same as the send function
     */
    int closeConnection();
};

#endif