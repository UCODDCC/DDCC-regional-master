#ifndef _DDCD_HANDLER_VECTOR_HANDLER_
#define _DDCD_HANDLER_VECTOR_HANDLER_

#include <string>
#include <regional-balancer/utils.hpp>
#include <regional-balancer/requesters/resourceRequester.hpp>
#include <regional-balancer/kernel/Client.hpp>


std::string vectorAdditionHandler(const std::string& message);

/**
 * generic vector operation handler, this function will redirect to the specific handler depending on the sub operation
 * at the request
 * @param message full client request message
 * @return response to the client
 */
std::string vectorHandler(const std::string& message);

#endif