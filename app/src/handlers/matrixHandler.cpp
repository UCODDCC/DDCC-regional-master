#include <regional-balancer/handlers/matrixHandler.hpp>

std::string matrixMultiplicationHanlder(const std::string& payload) {
    unsigned long int op_start, opcode_start, opcode_length, subopcode_start, subopcode_length;
    unsigned long int meta_start, meta_length;
    std::string size_a, size_b, size_ax, size_ay, size_bx, size_by;
    unsigned long int size_sepparator;

    op_start = payload.find('[') + 1;

    opcode_start = op_start;
    opcode_length = payload.find('|', opcode_start) - op_start;

    subopcode_start = payload.find('|', opcode_start + opcode_length) + 1;
    subopcode_length = payload.find('|', subopcode_start) - subopcode_start;

    meta_start = payload.find('|', subopcode_start + subopcode_length) + 1;
    meta_length = payload.find(']', meta_start) - meta_start;

    std::string metadata = payload.substr(meta_start, meta_length);

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

    return std::string("+<matrix multiplication handler>");
}

std::string matrixHandler(const std::string& payload){
    unsigned long int op_start, opcode_start, opcode_length, subopcode_start, subopcode_length;
    // unsigned long int meta_start, meta_length;
    op_start = payload.find('[') + 1;

    opcode_start = op_start;
    opcode_length = payload.find('|', opcode_start) - op_start;

    subopcode_start = payload.find('|', opcode_start + opcode_length) + 1;
    subopcode_length = payload.find('|', subopcode_start) - subopcode_start;

    // meta_start = payload.find('|', subopcode_start + subopcode_length) + 1;
    // meta_length = payload.find(']', meta_start) - meta_start;

    std::string subopcode = payload.substr(subopcode_start, subopcode_length);
    // std::string metadata = payload.substr(meta_start, meta_length);
    #ifdef DEBUG
        printf("sub-opcode:{%s}\n", subopcode.c_str());
    #endif
    if (subopcode == "multiplication")
        return matrixMultiplicationHanlder(payload);

    return std::string("-undefined matrix sub-operation<").append(subopcode).append(">");
}