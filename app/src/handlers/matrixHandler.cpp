#include <regional-balancer/handlers/matrixHandler.hpp>

std::string matrixMultiplicationHanlder(const std::string& message) {
    std::string size_a, size_b, size_ax, size_ay, size_bx, size_by;
    unsigned long int size_sepparator;
    int resource_location;

    std::string metadata = getMetaFromMessage(message);

    size_sepparator = metadata.find(',');
    size_a = metadata.substr(0, size_sepparator);
    size_b = metadata.substr(size_sepparator + 1, metadata.size());

    size_ax = size_a.substr(0, size_a.find('x'));
    size_ay = size_a.substr(size_a.find('x') + 1, size_a.size());
    size_bx = size_b.substr(0, size_b.find('x'));
    size_by = size_b.substr(size_b.find('x') + 1, size_b.size());

    #ifdef DEBUG
        printf("size: a:{%sx%s}, b:{%sx%s}\n", size_ax.c_str(), size_ay.c_str(), size_bx.c_str(), size_by.c_str());
    #endif

    if (atoi(size_ay.c_str()) != atoi(size_bx.c_str()))
        return std::string("-matrix sizes are incompatibles<").append(metadata).append(">");

    if (requestResource(getOpCodeFromMessage(message), &resource_location) != 0)
        return std::string("-timeout<resource reservation request wasn't responded>");

    return std::string("+<matrix multiplication handler>");
}

std::string matrixHandler(const std::string& message){
    std::string subopcode = getSubOpCodeFromMessage(message);
    #ifdef DEBUG
        printf("sub-opcode:{%s}\n", subopcode.c_str());
    #endif
    if (subopcode == "multiplication")
        return matrixMultiplicationHanlder(message);

    return std::string("-undefined matrix sub-operation<").append(subopcode).append(">");
}