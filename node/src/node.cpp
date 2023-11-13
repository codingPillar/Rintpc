#include "node.h"
#include "networkClient.h"
#include "topic.h"
#include <cstring>

using namespace rintpc;

Node::Node(const std::string &name): name(name), client(MASTER_NODE_ADDRESS) {}

Node::~Node(){
    client.closeConnection();
}

bool Node::pushTopicMessage(const TopicMessage &message){
    this->messagePublishQueue.push_front(message);
    /* TODO, ADD HANDLING FOR MAX QUEUE SIZE */
    return true;
}

bool Node::listenTopic(const std::string &name, TopicListenerCallback callback){
    auto previous = this->listeners.find(name);
    if(previous != this->listeners.end()) return false;
    this->listeners.insert({name, callback});
    return true;
}

TopicPublisher& Node::advertiseTopic(const std::string &topic){
    struct TopicMessage advertiseMessage;
    strncpy(advertiseMessage.name, topic.c_str(), TOPIC_NAME_SIZE);
    advertiseMessage.type = REGISTER_TOPIC_T;
    this->publishers.push_back(TopicPublisher(topic, *this));
    this->pushTopicMessage(advertiseMessage);
    return this->publishers[this->publishers.size() - 1];
}

void Node::singleSpin(){
    /* WE WANT TO RECEIVE DATA IF AVAILABLE */
    
    /* WE WANT TO SEND DATA IF AVAILABLE*/
    for(auto &message : this->messagePublishQueue)
        client.send((char *) &message, sizeof(TopicMessage));
    this->messagePublishQueue.clear();
}

void Node::spin(){
    /* MAYBE ADD A DELAY MECANISM */
    while(this->running) singleSpin();
}