#include <iostream>

#include "network.h"
#include "topicHandler.h"
#include "topicServer.h"

using namespace rintpc;
using namespace std;

/* CLASS TopicConnection */
TopicConnection::TopicConnection(Server *server, int connectionFd): Connection(server, connectionFd) {}

void TopicConnection::onReceive(char *buffer, unsigned int length){
    cout << "TOPIC RECEIVED" << endl;
    auto topicMessage = (TopicMessage*) buffer;
    cout << "NAME: " << topicMessage->name << endl;
    cout << "LENGTH: " << topicMessage->length << endl;
    cout << "MESSAGE: " << topicMessage->message << endl;
}

/* CLASS TopicServer */
TopicServer::TopicServer(uint32_t ip, uint16_t port): Server(ip, port) {
    this->topicHandler = TopicHandler::getTopicHandler();
};

Connection* TopicServer::getConnection(int connectionFd) {
    return new TopicConnection(this, connectionFd);
}

void TopicServer::cleanConnection(Connection *connection) {
    delete connection;
}