#ifndef RINTPC_NETWORK_H
#define RINTPC_NETWORK_H

#include <cstdint>

#include "constants.h"

namespace rintpc {

class Server;

class Connection{
public:
    Connection(Server *server, int connectionFd);
    virtual ~Connection() = default;
    
    virtual void onReceive(char *buffer, unsigned int length) = 0;
    int send(char *buffer, unsigned int length);

private:
    Server *server;
    int connectionFd;

    friend class Server;
};

/* ABSTRACTION FOR A TCP SERVER */
class Server{
public:
    Server(uint32_t ip, uint16_t port);
    ~Server() = default;

    virtual Connection* getConnection(int connectionFd) = 0;
    virtual void cleanConnection(Connection *connection) = 0;
    void RINTPC_BLOCKING listen();
    void stop();

protected:
    uint32_t ip;
    uint16_t port;
    int socketFd;
    bool running;
};

};

#endif //RINTPC_NETWORK_H