#include <string>
#include <pthread.h>

#include <regional-balancer/kernel/Client.hpp>
#include <regional-balancer/utils.hpp>

int requestResource(const std::string& resource_name, std::string* response, std::string* resource_location, int timeout = 60);