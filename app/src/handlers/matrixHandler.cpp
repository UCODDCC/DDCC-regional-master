#include <regional-balancer/handlers/matrixHandler.hpp>

std::string matrixMultiplicationHandler(const std::string& message) {
    std::string size_a, size_b, size_ax, size_ay, size_bx, size_by;
    unsigned long int size_separator;
    std::string resource_location;
    std::string response;
    std::string metadata = getMetaFromMessage(message);

    // checks metadata consistency
    size_separator = metadata.find(',');
    size_a = metadata.substr(0, size_separator);
    size_b = metadata.substr(size_separator + 1, metadata.size());

    size_ax = size_a.substr(0, size_a.find('x'));
    size_ay = size_a.substr(size_a.find('x') + 1, size_a.size());
    size_bx = size_b.substr(0, size_b.find('x'));
    size_by = size_b.substr(size_b.find('x') + 1, size_b.size());

    #ifdef DEBUG
        fprintf(stderr, "matrixMultiplicationHandler: size: a:{%sx%s}, b:{%sx%s}\n", size_ax.c_str(), size_ay.c_str(), size_bx.c_str(), size_by.c_str());
    #endif

    if (atoi(size_ay.c_str()) != atoi(size_bx.c_str()))
        return std::string("-matrix sizes are incompatibles<").append(metadata).append(">");

    // request a resource to the container balancer
    if (requestResource(getOpCodeFromMessage(message), &response, &resource_location) != 0)
        return response;

    #ifdef DEBUG
        fprintf(stderr, "matrixMultiplicationHandler: resource location at{%s}\n", resource_location.c_str());
        fprintf(stderr, "matrixMultiplicationHandler: sending {%s} to container\n", message.c_str());
    #endif
    // send the message to the container and waits for the result or timeout
    Client client(getAddressFromLocation(resource_location), std::atoi(getPortFromLocation(resource_location).c_str()));
    client.sendMessage(message);
    // return the response or error
    return client.listen();
}

std::string matrixHandler(const std::string& message){
    std::string subopcode = getSubOpCodeFromMessage(message);
    #ifdef DEBUG
        fprintf(stderr, "matrixHandler: sub-opcode:{%s}\n", subopcode.c_str());
    #endif
    if (subopcode == "multiplication")
        return matrixMultiplicationHandler(message);


    return std::string("-undefined matrix sub-operation<").append(subopcode).append(">");
}