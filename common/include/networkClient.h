#ifndef RINTPC_COMMON_CLIENT_H
#define RINTPC_COMMON_CLIENT_H

#include "network.h"

namespace rintpc {

class Client{
public:
    Client(const struct NodeAddress &nodeAddress);

    bool closeConnection();
    bool dataAvailable();
    int send(const char *buffer, unsigned int size);

private:
    /* METHODS */
    bool openConnection();

    /* ATTRIBS */    
    struct NodeAddress server;
    int fd = -1;
};

}

#endif //RINTPC_COMMON_CLIENT_H