#ifndef _DDCD_HANDLER_MAIN_HANDLER_
#define _DDCD_HANDLER_MAIN_HANDLER_

#include <regional-balancer/handlers/matrixHandler.hpp>
#include <regional-balancer/handlers/vectorHandler.hpp>
#include <regional-balancer/utils.hpp>

/**
 * first stage of the handling process, this function will parse the message and depending on the operation code, will
 * redirect the message to the corresponding handler at the next stage
 * @param message full client request message
 * @return response to the client
 */
std::string mainHandler(const std::string& message);

#endif