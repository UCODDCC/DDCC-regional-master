#include <regional-balancer/requesters/resourceRequester.hpp>


int requestResource(const std::string& resource_name, std::string* response, int* resource_location, int timeout){
    auto* client = new Client(DDCD_CONTAINER_ORCHESTRATOR_ADDRESS, DDCD_CONTAINER_ORCHESTRATOR_PORT);
    std::string request = std::string("+<").append(resource_name).append(">");
    client->sendMessage(request);
    *response = client->listen(timeout);
    printf("requestResource: response {%s}\n", response->c_str());
    *resource_location = -1;
    if ((*response)[0]=='+'){
        *resource_location = std::stoi(getPayloadFromMessage(*response));
        return 0;
    }
    return 1;
}