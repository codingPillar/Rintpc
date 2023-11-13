#include <iostream>

#include "networkServer.h"
#include "topicHandler.h"
#include "topicServer.h"

using namespace rintpc;
using namespace std;

/* CLASS TopicConnection */
TopicConnection::TopicConnection(Server *server, int connectionFd): Connection(server, connectionFd) {}

void TopicConnection::onReceive(char *buffer, unsigned int length, void *data){
    cout << "TOPIC MESSAGE RECEIVED WITH SIZE: " << length << endl;
    auto topicMessage = (TopicMessage*) buffer;
    auto topicHandler = (TopicHandler*) data; 
    switch (topicMessage->type) {
        case REGISTER_TOPIC_T:
            cout << "REGISTERING TOPIC: " << topicMessage->name << endl;
            topicHandler->registerTopic(topicMessage->name);
            break;
        case PUBLISH_MESSAGE_T:
            cout << "PUBLISHING MESSAGE ON TOPIC: " << topicMessage->name << endl;
            topicHandler->pushTopicMessage(topicMessage);
            break;
        default:
            cout << "TOPIC OPTION: " << topicMessage->type << " COULD NOT BE PARSED" << endl;
            break;
    };
}

/* CLASS TopicServer */
TopicServer::TopicServer(uint32_t ip, uint16_t port): Server(ip, port) {
    this->topicHandler = TopicHandler::getTopicHandler();
    this->data = this->topicHandler;
};

Connection* TopicServer::getConnection(int connectionFd) {
    return new TopicConnection(this, connectionFd);
}

void TopicServer::cleanConnection(Connection *connection) {
    delete connection;
}