#include <regional-master/kernel/Client.hpp>


void *listenThread(void* params) {
    auto* thread_params = (struct listenThreadParams*) params;
    char buffer[atoi(getenv("DDCC_CLIENT_BUFFER_SIZE"))];
    // read the message from the file descriptor until the terminating character appears
    do{
        bzero(buffer,atoi(getenv("DDCC_CLIENT_BUFFER_SIZE")));
        read(thread_params->socket, buffer, atoi(getenv("DDCC_CLIENT_BUFFER_SIZE")));
        thread_params->payload->append(buffer);
    } while (buffer[strlen(buffer)-1]!='>');
    // exit the thread and join the main process
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
            fprintf(stderr, "Client::Client: ERROR,Server cant be found.");
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
    listenThreadParams params{
            .socket = this->socket_fd_,
            .payload = &payload
    };
    // creates the thread and sets a timed out thread cancel
    pthread_create(&thread, nullptr, listenThread, (void *) &params);
    timeout_.tv_nsec = 0;
    timeout_.tv_sec = ((int)time(nullptr)) + timeout;
    retval = pthread_timedjoin_np(thread, nullptr, &timeout_);
    // if the thread has joined in time, copy the response into the payload at the struct
    if (retval == 0)
        return payload;
    // thread has failed to join, force the exit at the thread and copy a timeout error at the payload
    pthread_cancel(thread);
    #ifdef DEBUG
        if (atoi(getenv("DDCC_DEBUG_LEVEL")) > 0)
            fprintf(stderr, "Client::listen: connection timed out\n");
    #endif
    return std::string("-timeout<can not get message from orchestrator>");
}

int Client::closeConnection() {
    int retval = this->sendMessage("+<exit>");
    close(this->socket_fd_);
    return retval;
}