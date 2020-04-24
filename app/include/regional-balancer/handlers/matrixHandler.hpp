#ifndef _DDCD_HANDLER_MATRIX_HANDLER_
#define _DDCD_HANDLER_MATRIX_HANDLER_

#include <string>
#include <regional-balancer/utils.hpp>
#include <regional-balancer/requesters/resourceRequester.hpp>
#include <regional-balancer/kernel/Client.hpp>

/**
 * specific matrix multiplication handler, this function does multiples things:
 * - checks metadata consistency
 * - request a resource to the container balancer
 * - sends the data to the container
 * - waits for the container to return the result
 * - returns the container response
 * @param message full client request message
 * @return response to the client
 */
std::string matrixMultiplicationHandler(const std::string& message);

/**
 * generic matrix operation handler, this function will redirect to the specific handler depending on the sub operation
 * at the request
 * @param message full client request message
 * @return response to the client
 */
std::string matrixHandler(const std::string& message);

#endif