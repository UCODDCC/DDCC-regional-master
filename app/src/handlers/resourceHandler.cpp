#include <regional-master/handlers/resourceHandler.hpp>

std::string resourceHandler(const std::string& message) {
    std::string resource_location;
    std::string response;

    #ifdef DEBUG
        fprintf(stderr,"resourceHandler: opcode:{%s}\n", getOpCodeFromMessage(message).c_str());
        fprintf(stderr,"resourceHandler: subopcode:{%s}\n", getSubOpCodeFromMessage(message).c_str());
    #endif

    if (requestResource(getOpCodeFromMessage(message), &response, &resource_location) != 0) {
        return response; // error on response
    }

    LWClient client(getAddressFromLocation(resource_location), std::atoi(getPortFromLocation(resource_location).c_str()));
    // send the message to the working node
    client.sendMessage(message);
    // return the working node response
    return client.listenAndExit();
}