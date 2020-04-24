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


/**
 * All the handlers must follow this type
 */
typedef std::string (*handlerType)(const std::string&);

/**
 * This struct stores the necessary information for the thread to read, process and respond to the client request
 */
struct serverConnection {
    int socket_fd = -1;
    struct sockaddr client_sock_addr{};
    socklen_t len{};
};

/**
 * Threaded function where the request will be process, in this function the followinf is done:
 * - The message is read from the file descriptor
 * - The message is passed to the handler
 * - the response of the handler is send back to the client
 * @param handler handler function
 * @param client server connection struct necesarry for sending the response as this thread will not join the main
 * process
 */
void handleNextConnectionThreaded(handlerType handler, serverConnection client);

/**
 * A very simple generic TCP server
 * This server does not saves the client sessions, when a request is made, the server will dispatch it via the handler
 * specified in the constructor and one done, the socket will be closed
 *
 * Each request is handled in a dedicated detached threads, the execution here is fully sequential, while the main
 * thread listens for the next request.
 */
class Server {

private:
    int server_fd_;
    sockaddr_in server_sock_addr_{};
    std::vector<std::thread> threads_;

public:
    handlerType handler_;

    /**
     * Class contructor
     * @param portno port where the server will be listening on all addresses
     * @param requestHandler handler function
     */
    Server(int portno, handlerType requestHandler);

    /**
     * Serial part of the request process
     * this function will accept the connection and launch a thread to do the rest of processing
     */
    void handleNextConnection();

    /**
     * Closes the server socket
     */
    void exit();
};

#endif
