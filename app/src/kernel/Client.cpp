#include <regional-balancer/kernel/Client.hpp>



void *listenThread(void* params) {
    auto* thread_params = (struct listenThreadParams*) params;
    char buffer[CLIENT_BUFFER_SIZE];
    do{
        bzero(buffer, CLIENT_BUFFER_SIZE);
        read(thread_params->socket, buffer, CLIENT_BUFFER_SIZE);
        thread_params->payload->append(buffer);
    } while (buffer[strlen(buffer)-1]!='>');
    pthread_exit(nullptr);
}

Client::Client(const std::string& addr, int portno) {
    this->socket_fd_ = socket(AF_INET, SOCK_STREAM, 0);
    // TODO: if error

    this->server_dir_.sin_family = AF_INET;
    this->server_dir_.sin_addr.s_addr = inet_addr(addr.c_str());
    this->server_dir_.sin_port = htons(portno);

    this->server_dir_len_ = sizeof(this->server_dir_);

    {
        int ret_val;
        ret_val = connect(
                this->socket_fd_,
                (sockaddr*) &this->server_dir_,
                this->server_dir_len_
        );
        // TODO: finish error
        if (ret_val == -1){
            fprintf(stderr, "ERROR,Server cant be found.");
        }
    }
}

int Client::sendMessage(const std::string& payload) {
    return send(
            this->socket_fd_,
            payload.c_str(),
            strlen(payload.c_str()),
            0
    );
}

std::string Client::listen(int timeout) {
    int retval;
    struct timespec timeout_{};
    std::string payload;
    pthread_t thread;
    listenThreadParams params {
        .socket = this->socket_fd_,
        .payload = &payload
    };

    pthread_create(&thread, nullptr, listenThread, (void*) &params);
    for (; timeout > 0; --timeout) {
        timeout_.tv_nsec = 0; timeout_.tv_sec = time(nullptr) + 1;
        retval = pthread_timedjoin_np(thread, nullptr, &timeout_);
        if (retval == 0)
            return payload;
    }
    pthread_cancel(thread);
    return std::string("-timeout<can not get message from orchestrator>");
}

int Client::closeConnection() {
    return this->sendMessage("+<exit>");
}