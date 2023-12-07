#include "node.h"
#include "networkClient.h"
#include "topic.h"
#include <cstring>
#include <string>

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

bool Node::shouldStop(){
    /* TODO, SYNCHRONIZE WITH MASTER AND ADD HANDLING FOR SIGNALS */
    return false;
}

bool Node::listenTopic(const std::string &name, TopicListenerCallback callback){
    auto previous = this->listeners.find(name);
    if(previous != this->listeners.end()) return false;
    this->listeners.insert({name, callback});
    TopicMessage message = {.type = SUBSCRIBE_TOPIC_T, .length = 0};
    strncpy(message.name, name.c_str(), TOPIC_NAME_SIZE);
    this->pushTopicMessage(message);
    return true;
}

TopicPublisher& Node::advertiseTopic(const std::string &topic){
    struct TopicMessage advertiseMessage = {.type = REGISTER_TOPIC_T, .length = 0};
    strncpy(advertiseMessage.name, topic.c_str(), TOPIC_NAME_SIZE);
    this->publishers.push_back(TopicPublisher(topic, *this));
    this->pushTopicMessage(advertiseMessage);
    return this->publishers[this->publishers.size() - 1];
}

void Node::receiveMessage(){
    if(!this->client.dataAvailable()) return;
    this->client.receive();
    const TopicMessage *buffer = (const TopicMessage *) this->client.getBuffer();
    auto callback = this->listeners.find(std::string(buffer->name));
    /* NO LISTENER (SHOULD NOT REALLY HAPPEN) */
    if(callback == this->listeners.end()) return;
    callback->second(buffer->message, buffer->length);
}

void Node::singleSpin(){
    /* WE WANT TO RECEIVE DATA IF AVAILABLE */
    receiveMessage();

    /* WE WANT TO SEND DATA IF AVAILABLE*/
    while(this->messagePublishQueue.size() > 0){
        auto &message = this->messagePublishQueue.back();
        client.send((char *) &message, sizeof(TopicMessage) - (TOPIC_MESSAGE_SIZE - message.length));
        this->messagePublishQueue.pop_back();
    }
}

void Node::spin(){
    /* MAYBE ADD A DELAY MECANISM */
    while(this->running) singleSpin();
}