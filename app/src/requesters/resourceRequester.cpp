#include <regional-master/requesters/resourceRequester.hpp>


int requestResource(const std::string& resource_name, std::string* response, std::string* resource_location, int timeout){
    LWClient* client;
    if (DDCC_USE_REGIONAL_BALANCER)
        client = new LWClient(DDCD_REGIONAL_BALANCER_ADDRESS, DDCD_REGIONAL_BALANCER_PORT);
    else
        client = new LWClient(DDCD_CONTAINER_ORCHESTRATOR_ADDRESS, DDCD_CONTAINER_ORCHESTRATOR_PORT);

    std::string request = std::string("+<").append(resource_name).append(">");
    client->sendMessage(request);
    *response = client->listenAndExit(timeout);
    #ifdef DEBUG
        fprintf(stderr, "requestResource: response {%s}\n", response->c_str());
    #endif
    *resource_location = "";
    if ((*response)[0]=='+'){
        *resource_location = getPayloadFromMessage(*response);
        return 0;
    }
    return 1;
}