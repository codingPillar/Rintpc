#ifndef RINTPC_NETWORK_H
#define RINTPC_NETWORK_H

#include <cstdint>
#include <vector>
#include <thread>

#include "constants.h"
#include "network.h"

namespace rintpc {

class Server;

class Connection{
public:
    Connection(Server *server, NodeAddress remote, int connectionFd);
    virtual ~Connection() = default;
    
    virtual void onReceive(char *buffer, unsigned int length, void *data = nullptr) = 0;
    int send(const char *buffer, unsigned int length);
    bool dataAvailable();
    NodeAddress getRemoteAddress();

protected:    
    NodeAddress remote;
    
private:
    Server *server;
    int connectionFd;

    friend class Server;
};

/* ABSTRACTION FOR A TCP SERVER */
class Server{
public:
    Server(uint32_t ip, uint16_t port);
    virtual ~Server() = default;

    virtual Connection* getConnection(NodeAddress remote, int connectionFd) = 0;
    virtual void cleanConnection(Connection *connection) = 0;
    void RINTPC_BLOCKING listen();
    void stop();

protected:
    NodeAddress address;
    int socketFd;
    bool running;
    void *data = nullptr;

    std::vector<Connection*> connections;

private:
    void startReceiveThread();
    void cleanReceiveThread();

    std::thread *thread = nullptr;
};

};

#endif //RINTPC_NETWORK_H