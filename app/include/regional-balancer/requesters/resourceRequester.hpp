#include <string>
#include <pthread.h>

#include <regional-balancer/kernel/Client.hpp>

int requestResource(const std::string& resource_name, int* resource_location, int timeout = 60);