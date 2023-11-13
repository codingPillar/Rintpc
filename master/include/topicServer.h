#ifndef RINTPC_TOPIC_SERVER
#define RINTPC_TOPIC_SERVER

#include "network.h"
#include "networkServer.h"
#include "topicHandler.h"

namespace rintpc {

class TopicConnection: public Connection{
public:
    TopicConnection(Server *server, NodeAddress remote, int connectionFd);

    virtual void onReceive(char *buffer, unsigned int length, void *data = nullptr) override;

private:
};

/* EXPECTS HOST FORMAT IP AND PORT */
class TopicServer: public Server{
public:
    TopicServer(uint32_t ip, uint16_t port);

    virtual Connection* getConnection(NodeAddress remote, int connectionFd) override;
    virtual void cleanConnection(Connection *connection) override;

private:
    TopicHandler *topicHandler;
};

}

#endif //RINTPC_TOPIC_SERVER