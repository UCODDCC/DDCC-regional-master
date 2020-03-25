#include <regional-balancer/handlers/mainHandler.hpp>

std::string mainHandler(const std::string& payload){
    unsigned long int op_start, op_length;
    op_start = payload.find('[') + 1;
    std::string opcode = payload.substr(op_start, payload.length());
    opcode = opcode.substr(0, opcode.find('|'));
    #ifdef DEBUG
        printf("opcode:{%s}\n", opcode.c_str());
    #endif

    if (opcode == "matrix")
        return matrixHandler(payload);

    return std::string("-undefined opcode<").append(opcode).append(">");
}