#ifndef _DDCD_HANDLER_MATRIX_HANDLER_
#define _DDCD_HANDLER_MATRIX_HANDLER_

#include <string>
#include <regional-balancer/configuration.hpp>
#include <regional-balancer/utils.hpp>
#include <regional-balancer/requesters/resourceRequester.hpp>
#include <regional-balancer/kernel/Client.hpp>

std::string matrixMultiplicationHanlder(const std::string& payload);

std::string matrixHandler(const std::string& message);

#endif