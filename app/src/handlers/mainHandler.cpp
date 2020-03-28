#include <regional-balancer/handlers/mainHandler.hpp>

std::string mainHandler(const std::string& message) {
    std::string opcode = getOpCodeFromMessage(message);
    #ifdef DEBUG
        printf("opcode:{%s}\n", opcode.c_str());
    #endif

    if (opcode == "matrix")
        return matrixHandler(message);

    return std::string("-undefined opcode<").append(opcode).append(">");
}