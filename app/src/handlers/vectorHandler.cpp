#include <regional-balancer/handlers/matrixHandler.hpp>

std::string vectorAdditionHandler(const std::string& message) {
    std::string resource_location;
    std::string response;

    if (requestResource(getOpCodeFromMessage(message), &response, &resource_location) != 0)
        return response;

    Client client(getAddressFromLocation(resource_location), std::atoi(getPortFromLocation(resource_location).c_str()));
    client.sendMessage(message);
    // return the response or error
    return client.listen();
}

std::string vectorHandler(const std::string& message){
    std::string subopcode = getSubOpCodeFromMessage(message);
    #ifdef DEBUG
        printf("vectorHandler: sub-opcode:{%s}\n", subopcode.c_str());
    #endif
    if (subopcode == "addition")
        return vectorAdditionHandler(message);


    return std::string("-undefined vector sub-operation<").append(subopcode).append(">");
}