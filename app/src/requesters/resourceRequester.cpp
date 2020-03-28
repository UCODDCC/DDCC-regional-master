#include <regional-balancer/requesters/resourceRequester.hpp>



int requestResource(const std::string& resource_name, int* resource_location, int timeout){
    auto* client = new Client(DDCD_CONTAINER_ORCHESTRATOR_ADDRESS, DDCD_CONTAINER_ORCHESTRATOR_PORT);
    std::string request = std::string("+<").append(resource_name).append(">");
    client->sendMessage(request);
    std::string response = client->listen(timeout);
    printf("response {%s}", response.c_str());
    return 0;
}