#ifndef RINTPC_TOPIC_SERVER
#define RINTPC_TOPIC_SERVER

#include "networkServer.h"
#include "topicHandler.h"

namespace rintpc {

class TopicConnection: public Connection{
public:
    TopicConnection(Server *server, int connectionFd);

    virtual void onReceive(char *buffer, unsigned int length) override;

private:
};

class TopicServer: public Server{
public:
    TopicServer(uint32_t ip, uint16_t port);

    virtual Connection* getConnection(int connectionFd) override;
    virtual void cleanConnection(Connection *connection) override;

private:
    TopicHandler *topicHandler;
};

}

#endif //RINTPC_TOPIC_SERVER