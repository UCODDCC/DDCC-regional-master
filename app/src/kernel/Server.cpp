#include <regional-balancer/kernel/Server.hpp>

void handleNextConnectionThreaded(handlerType handler, serverConnection client) {
    char buffer[BUFF_SIZE];
    std::string payload;
    do{
        bzero(buffer, BUFF_SIZE);
        read(client.socket_fd, buffer, BUFF_SIZE);
        payload.append(buffer);
    } while (buffer[strlen(buffer)-1]!='>');

    std::string response = handler(payload);

    send(
            client.socket_fd,
            response.c_str(),
            strlen(response.c_str()),
            0
    );
    #ifdef DEBUG
        printf("received {%s}%lu\nsending back {%s}:%lu\n", payload.c_str(), strlen(payload.c_str()), response.c_str(), strlen(response.c_str()));
    #endif

    close(client.socket_fd);
}

Server::Server(int portno, handlerType requestHandler) {
    int retval;

    this->connectionCap_ = 50;
    bzero((char*)&this->server_sock_addr_, sizeof(server_sock_addr_));
    this->server_sock_addr_.sin_port = htons(portno);
    this->server_sock_addr_.sin_family = AF_INET;
    this->server_sock_addr_.sin_addr.s_addr = htonl(INADDR_ANY);
    this->handler_ = requestHandler;

    this->server_fd_ = socket(AF_INET, SOCK_STREAM, 0);
    if (this->server_fd_ < 0)
        throw std::runtime_error("error: can not open socket");

    retval = bind(
            this->server_fd_,
            (const sockaddr*) &this->server_sock_addr_,
            sizeof(this->server_sock_addr_)
    );
    if (retval < 0)
        throw std::runtime_error("error: can not bind to socket");

    retval = listen(this->server_fd_, 5); // 5 is the maximum size permitted by most systems
    if (retval == -1)
        throw std::runtime_error("error: can not set socket to listen on port");
}


void Server::handleNextConnection() {
    serverConnection client;
    client.socket_fd = accept(
            this->server_fd_,
            (sockaddr*) &client.client_sock_addr,
            &client.len
    );
    if (client.socket_fd == -1) {
        return;
    }
    std::thread t(handleNextConnectionThreaded, this->handler_, client);
    t.detach();
}

int Server::getConnectionCap() const {
    return this->connectionCap_;
}

void Server::setConnectionCap(int cap) {
    if (cap > 0)
        this->connectionCap_ = cap;
}

int Server::getNumberOfConnections() const {
    return this->threads_.size();
}

void Server::exit() {
    close(this->server_fd_);
    printf("server closed\n");
}