#include <iostream>
#include <assert.h>
#include <vector>

#include "networkServer.h"
#include "topicHandler.h"

using namespace std;

using namespace rintpc;

TopicHandler TopicHandler::instance;

TopicHandler* TopicHandler::getTopicHandler(){
    return &TopicHandler::instance;
}

bool TopicHandler::registerTopic(const std::string &name){
    this->lockBoth();
    auto elem = this->messageQueue.find(name);
    if(elem != this->messageQueue.end()){
        cout << "TOPIC: " << name << " ALREADY REGISTERED USER OTHER NAME" << endl;
        this->unlockBoth();
        return false;
    }
    this->messageQueue.insert({name, std::list<TopicMessage>()});
    this->topicListeners.insert({name, std::vector<Connection*>()});
    cout << "NEW TOPIC: " << name << " REGISTERED" << endl;
    this->unlockBoth();
    return false;
}

bool TopicHandler::pushTopicMessage(const struct TopicMessage *topicMessage){
    this->messageMut.lock();
    auto topicMessages = this->messageQueue.find(topicMessage->name);
    if(topicMessages == this->messageQueue.end()){
        cout << "COULD NOT FIND TOPIC WITH NAME: " << topicMessage->name << " RESGITER NODE FIRST" << endl;
        this->messageMut.unlock();
        return false;
    }
    topicMessages->second.push_back(*topicMessage);
    this->messageMut.unlock();
    return true;
}

void TopicHandler::addTopicListener(const string &name, Connection *listener){
    this->listenersMut.lock();
    auto listeners = this->topicListeners.find(name);
    if(listeners == this->topicListeners.end()){
        cout << "COULD NOT FIND TOPIC WITH NAME: " << name << " REGISTER NODE FIRST BEFORE ADDING LISTENER" << endl;
        this->listenersMut.unlock();
        return;
    }
    listeners->second.push_back(listener);
    this->listenersMut.unlock();
}

std::vector<std::string> TopicHandler::getTopics(){
    std::vector<std::string> topics;
    for(auto topic : this->messageQueue)
        topics.push_back(topic.first);
    return topics;
}

pair<TopicMessage, vector<Connection*>> TopicHandler::popTopicMessage(const std::string &name){
    this->lockBoth();
    auto messages = this->messageQueue.find(name);
    auto listeners = this->topicListeners.find(name);
    if(messages == this->messageQueue.end() || listeners == this->topicListeners.end()){
        cout << "COULD NOT FIND TOPIC: " << name << ", REGISTER FIRST BEFORE POPING MESSAGE" << endl;
        this->unlockBoth();
        return {{}, vector<Connection*>()};
    }
    TopicMessage message = messages->second.front();
    messages->second.pop_front();
    this->unlockBoth();
    return {message, listeners->second};
}

bool TopicHandler::removeTopicListener(const std::string &name, const struct NodeAddress &listener){
    this->listenersMut.lock();
    auto listeners = this->topicListeners.find(name);
    if(listeners == this->topicListeners.end()){
        cout << "TOPIC DOES NOT EXIST, CANNOT REMOVE LISTENER" << endl;
        this->listenersMut.unlock();
        return false;
    }
    for(unsigned int i = 0; i < listeners->second.size(); i++){
        if(listeners->second[i]->getRemoteAddress().ip != listener.ip || listeners->second[i]->getRemoteAddress().port != listener.port) continue;
        /* TODO, CLEAR CURRENT ELEMENT */
        assert(false);
        break;
    }
    this->listenersMut.unlock();
    return true;
}

void TopicHandler::lockBoth(){
    /* WE WANT TO LOCK AND UNLOCK IN SAME ORDER AS OTHER THREAD THAT NEED THIS TO AVOID BLOCKING */
    this->messageMut.lock();
    this->listenersMut.lock();
}

void TopicHandler::unlockBoth(){
    /* SAME NOTE AS lockBoth FUNCTION */
    this->listenersMut.unlock();
    this->messageMut.unlock();
}

/* PRIVATE */
TopicHandler::TopicHandler() {}

