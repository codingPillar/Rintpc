#ifndef RINTPC_COMMON_CLIENT_H
#define RINTPC_COMMON_CLIENT_H

#include "network.h"
#include <array>

namespace rintpc {

class Client{
public:
    Client(const struct NodeAddress &nodeAddress);

    bool closeConnection();
    bool dataAvailable();
    int send(const char *buffer, unsigned int size);
    int receive();
    const char* getBuffer();

private:
    /* METHODS */
    bool openConnection();

    /* ATTRIBS */
    std::array<char, SOCK_RCV_BUFF_MAX_SIZE> buffer;
    struct NodeAddress server;
    int fd = -1;
};

}

#endif //RINTPC_COMMON_CLIENT_H