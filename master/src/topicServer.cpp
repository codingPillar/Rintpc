#include <iostream>

#include "networkServer.h"
#include "topicHandler.h"
#include "topicServer.h"

using namespace rintpc;
using namespace std;

/* CLASS TopicConnection */
TopicConnection::TopicConnection(Server *server, int connectionFd): Connection(server, connectionFd) {}

void TopicConnection::onReceive(char *buffer, unsigned int length, void *data){
    cout << "TOPIC RECEIVED" << endl;
    auto topicMessage = (TopicMessage*) buffer;
    auto topicHandler = (TopicHandler*) data; 
    /* TODO, SHOULD HAVE A DIFFERENT PROTOCOL FOR FIRST REGISTRATION OF TOPIC */
    topicHandler->pushTopicMessage(topicMessage);
    cout << "NAME: " << topicMessage->name << endl;
    cout << "LENGTH: " << topicMessage->length << endl;
    cout << "MESSAGE: " << topicMessage->message << endl;
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