#include <regional-balancer/utils.hpp>

std::string getDelimitedMessage(const std::string& message, char opening_delimiter, char close_delimiter) {
    unsigned int del1 = -1, del2 = -1;
    del1 = message.find(opening_delimiter) + 1;
    del2 = message.find(close_delimiter);
    if (del1 == -1 || del2 == -1)
        return "";
    return message.substr(del1, del2 - del1);
}

std::string getPayloadFromMessage(const std::string& message) {
    return getDelimitedMessage(message, '<', '>');
}

std::string getOperationFromMessage(const std::string& message) {
    return getDelimitedMessage(message, '[', ']');
}

std::string getErrorFromMessage(const std::string& message) {
    return getDelimitedMessage(message, '-', '<');
}

std::string getOpCodeFromMessage(const std::string& message) {
    std::string operation = getOperationFromMessage(message);
    unsigned long int opcode_start, opcode_length;

    opcode_start = 0;
    opcode_length = operation.find('|', opcode_start) - opcode_start;

    return operation.substr(opcode_start, opcode_length);
}

std::string getSubOpCodeFromMessage(const std::string& message) {
    std::string operation = getOperationFromMessage(message);
    unsigned long int opcode_start, opcode_length, subopcode_start, subopcode_length;

    opcode_start = 0;
    opcode_length = operation.find('|', opcode_start) - opcode_start;

    subopcode_start = operation.find('|', opcode_start + opcode_length) + 1;
    subopcode_length = operation.find('|', subopcode_start) - subopcode_start;

    return operation.substr(subopcode_start, subopcode_length);
}

std::string getMetaFromMessage(const std::string& message) {
    std::string operation = getOperationFromMessage(message);
    unsigned long int opcode_start, opcode_length, subopcode_start, subopcode_length, meta_start, meta_length;

    opcode_start = 0;
    opcode_length = operation.find('|', opcode_start) - opcode_start;

    subopcode_start = operation.find('|', opcode_start + opcode_length) + 1;
    subopcode_length = operation.find('|', subopcode_start) - subopcode_start;

    meta_start = operation.find('|', subopcode_start + subopcode_length) + 1;
    meta_length = operation.size() - meta_start;

    return operation.substr(meta_start, meta_length);
}

std::string getAddressFromLocation(const std::string& message) {
    return message.substr(0, message.find(':'));
}

std::string getPortFromLocation(const std::string& message) {
    return message.substr(message.find(':') + 1, message.length());
}