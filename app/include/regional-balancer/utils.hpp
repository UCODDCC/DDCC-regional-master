#ifndef _DDCD_UTILS_
#define _DDCD_UTILS_

#include <string>

std::string getDelimitedMessage(const std::string& message, char opening_delimiter, char close_delimiter);
std::string getPayloadFromMessage(const std::string& message);
std::string getOperationFromMessage(const std::string& message);
std::string getErrorFromMessage(const std::string& message);
std::string getOpCodeFromMessage(const std::string& message);
std::string getSubOpCodeFromMessage(const std::string& message);
std::string getMetaFromMessage(const std::string& message);

#endif