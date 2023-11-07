#include <cstdlib>
#include <iostream>
#include <sys/socket.h>
#include <netinet/in.h>
#include <unistd.h>

#include "constants.h"
#include "network.h"
#include "networkClient.h"

using namespace std;
using namespace rintpc;

static constexpr unsigned int MAX_ITERATION = 20; 
static constexpr unsigned int MIN_PORT_NUMBER = 1024; 

Client::Client(const struct NodeAddress &nodeAddress): server(nodeAddress) {
    openConnection();
}

bool Client::openConnection(){
    this->fd = socket(AF_INET, SOCK_STREAM, 0);
    if(this->fd < 0){
        cout << "COULD NOT OPEN SOCKET" << endl;
        return false;
    }
    struct sockaddr_in local = {.sin_family = AF_INET, .sin_port = 0, .sin_addr = {.s_addr = htonl(LOCAL_HOST_IP)}};
    int result = 0;
    unsigned int counter = 0;
    do{
        local.sin_port = MIN_PORT_NUMBER + rand() % ((1 << 16) - MIN_PORT_NUMBER);
        result = bind(this->fd, (struct sockaddr*) &local, sizeof(struct sockaddr_in));
    }while(counter++ < MAX_ITERATION && result < 0);
    if(result < 0){
        cout << "COULD NOT BIND CLIENT SOCKET TO VALID ADDRESS USING IP: " << formatIP(local.sin_addr.s_addr) << endl;
        close(this->fd);
        return false;
    }
    struct sockaddr_in destination = {.sin_family = AF_INET, .sin_port = server.port, .sin_addr = {.s_addr = server.ip}};
    result = connect(this->fd, (const struct sockaddr*) &destination, sizeof(struct sockaddr_in));
    if(result < 0){
        cout << "COULD NOT CONNECT TO ADDRESS : " << formatIP(destination.sin_addr.s_addr) << ":" << ntohs(destination.sin_port) << endl;
        return false;
    }
    cout << "NEW CONNECTION WITH : " << formatIP(destination.sin_addr.s_addr) << ":" << ntohs(destination.sin_port) << " FROM : " << formatIP(local.sin_addr.s_addr) << ":" << ntohs(local.sin_port) << endl;
    return true;
}

bool Client::closeConnection(){
    return close(this->fd) == 0;
}

int Client::send(const char *buffer, unsigned int size){
    int result = ::send(this->fd, buffer, size, 0);
    cout << "SEND RESULT : " << result << endl;
    return result;
}

