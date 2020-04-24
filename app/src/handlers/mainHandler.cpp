#include <regional-balancer/handlers/mainHandler.hpp>

std::string mainHandler(const std::string& message) {
    std::string opcode = getOpCodeFromMessage(message);
    #ifdef DEBUG
        if (atoi(getenv("DDCC_DEBUG_LEVEL")) > 0)
            fprintf(stderr,"opcode:{%s}\n", opcode.c_str());
    #endif

    if (opcode == "matrix")
        return matrixHandler(message);

    if (opcode == "vector")
        return vectorHandler(message);

    return std::string("-undefined opcode<").append(opcode).append(">");
}