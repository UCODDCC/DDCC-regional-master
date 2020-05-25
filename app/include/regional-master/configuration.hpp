#ifndef _DDCD_CONFIG_
#define _DDCD_CONFIG_

#define DDCD_CLIENT_BUFFER_SIZE 2048
#define DDCC_SERVER_BUFF_SIZE 2048
#define DDCD_REGIONAL_MASTER_PORT 7654 // THIS MACHINE
#define DDCD_REGIONAL_BALANCER_ADDRESS "10.10.1.1"
#define DDCD_REGIONAL_BALANCER_PORT 7655
#define DDCD_CONTAINER_ORCHESTRATOR_ADDRESS "10.10.1.1"
#define DDCD_CONTAINER_ORCHESTRATOR_PORT 7657

#define DDCC_USE_REGIONAL_BALANCER true

#define DDCC_LISTEN_TIME_OUT 60

#endif