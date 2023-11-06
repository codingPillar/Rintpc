#include <iostream>
#include <sys/socket.h>
#include <netinet/in.h>
#include <unistd.h>

#include "constants.h"
#include "network.h"
#include "networkClient.h"

using namespace std;
using namespace rintpc;

Client::Client(const struct NodeAddress &nodeAddress): server(nodeAddress) {}

bool Client::openConnection(){
    this->fd = socket(AF_INET, SOCK_STREAM, 0);
    if(this->fd < 0){
        cout << "COULD NOT OPEN SOCKET" << endl;
        return false;
    }
    struct sockaddr_in local = {.sin_family = AF_INET, .sin_port = 0, .sin_addr = {.s_addr = htonl(LOCAL_HOST_IP)}};
    int result = bind(this->fd, (struct sockaddr*) &local, sizeof(struct sockaddr_in));
    if(result < 0){
        cout << "COULD NOT BIND TO ADDRESS: " << local.sin_addr.s_addr << endl;
        close(this->fd);
        return false;
    }
    struct sockaddr_in destination = {.sin_family = AF_INET, .sin_port = server.port, .sin_addr = {.s_addr = server.ip}};
    int conndectionfd = connect(this->fd, (const struct sockaddr*) &destination, sizeof(struct sockaddr_in));
    const char buffer[] = "HOLLA"; 
    send(conndectionfd, buffer, sizeof(buffer), 0);
    close(conndectionfd);
    return true;
}

