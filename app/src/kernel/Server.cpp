#include <regional-balancer/kernel/Server.hpp>

void handleNextConnectionThreaded(handlerType handler, serverConnection client) {
    char buffer[DDCD_SERVER_BUFF_SIZE];
    std::string payload;

    // read the message from the file descriptor until the terminating character appears
    do{
        bzero(buffer, DDCD_SERVER_BUFF_SIZE);
        read(client.socket_fd, buffer, DDCD_SERVER_BUFF_SIZE);
        payload.append(buffer);
    } while (buffer[strlen(buffer)-1]!='>');

    #ifdef DEBUG
        printf("handleNextConnectionThreaded: received {%s}%lu\n", payload.c_str(), strlen(payload.c_str()));
    #endif
    // process the message via the handler
    std::string response = handler(payload);

    // send back the response
    send(
            client.socket_fd,
            response.c_str(),
            strlen(response.c_str()),
            0
    );
    #ifdef DEBUG
        printf("handleNextConnectionThreaded: sending back {%s}:%lu\n", response.c_str(), strlen(response.c_str()));
    #endif
    // close the client socket
    close(client.socket_fd);
}

Server::Server(int portno, handlerType requestHandler) {
    int retval;
    this->handler_ = requestHandler;

    // clear and sets the server address
    bzero((char*)&this->server_sock_addr_, sizeof(server_sock_addr_));
    this->server_sock_addr_.sin_port = htons(portno);
    this->server_sock_addr_.sin_family = AF_INET;
    this->server_sock_addr_.sin_addr.s_addr = htonl(INADDR_ANY);

    // open the socket
    this->server_fd_ = socket(AF_INET, SOCK_STREAM, 0);
    if (this->server_fd_ < 0)
        throw std::runtime_error("error: can not open socket");

    // bind the socket to the port
    retval = bind(
            this->server_fd_,
            (const sockaddr*) &this->server_sock_addr_,
            sizeof(this->server_sock_addr_)
    );
    if (retval < 0)
        throw std::runtime_error("error: can not bind to socket");

    // set a queue of 5 to listen in at the binded port
    retval = listen(this->server_fd_, 5); // 5 is the maximum size permitted by most systems
    if (retval == -1)
        throw std::runtime_error("error: can not set socket to listen on port");
}


void Server::handleNextConnection() {
    serverConnection client;
    // accepts the request from the client
    client.socket_fd = accept(
            this->server_fd_,
            (sockaddr*) &client.client_sock_addr,
            &client.len
    );
    if (client.socket_fd == -1) {
        return;
    }
    // launches the thread and detaches it from the main process
    std::thread t(handleNextConnectionThreaded, this->handler_, client);
    t.detach();
}

void Server::exit() {
    close(this->server_fd_);
    printf("server closed\n");
}