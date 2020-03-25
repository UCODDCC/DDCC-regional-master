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

#define CLIENT_BUFFER_SIZE 2048
struct listenThreadParams {
    int socket;
    std::string* payload;
};
void* listenThread(void* params);

/**
 * This simple client starts a connection to a server, one this is made (automatic) it can send and receive payloads
 * to and from that server.
 */
class Client {
private:
    int socket_fd_;
    sockaddr_in server_dir_{};
    socklen_t server_dir_len_;
public:
    Client(const std::string& addr, int portno);

    int sendMessage(const std::string& payload);

    std::string listen(int timeout = 60);

    int closeConnection();

};

#endif