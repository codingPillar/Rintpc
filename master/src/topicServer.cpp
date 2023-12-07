#include <iostream>
#include <thread>
#include <vector>

#include "network.h"
#include "networkServer.h"
#include "topicHandler.h"
#include "topicServer.h"
#include "clock.h"

using namespace rintpc;
using namespace std;

/* CLASS TopicConnection */
TopicConnection::TopicConnection(Server *server, NodeAddress remote, int connectionFd): Connection(server, remote, connectionFd) {}

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
        case SUBSCRIBE_TOPIC_T:
            cout << "SUBSCRIBING TO TOPIC: " << topicMessage->name << endl;
            topicHandler->addTopicListener(std::string(topicMessage->name), this);
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
    //this->startNotifierThread();
};

Connection* TopicServer::getConnection(NodeAddress remote, int connectionFd) {
    return new TopicConnection(this, remote, connectionFd);
}

void TopicServer::cleanConnection(Connection *connection) {
    delete connection;
}

void TopicServer::startNotifierThread(){
    auto threadBody = [this](){
        cout << "START NOTIFIER THREAD" << endl;
        Clock rate(5);
        while(this->running){
            std::vector<std::string> topics = this->topicHandler->getTopics();
            for(std::string &topic : topics){
                std::pair<TopicMessage, std::vector<Connection*>> messagefd = 
                    this->topicHandler->popTopicMessage(topic);
                if(messagefd.first.message[0] == '\0') continue;
                /* SEND MESSAGE TO ALL LISTENERS */
                for(Connection *connection : messagefd.second)
                    connection->send((const char*) &messagefd.first, sizeof(TopicMessage));
            }
            rate.sleep();
        }
    };
    this->notifierThread = new std::thread(threadBody);
}

void TopicServer::stopNotifierThread(){
    this->notifierThread->join();
    delete this->notifierThread;
}