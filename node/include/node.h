#ifndef RINTPC_NODE_H
#define RINTPC_NODE_H

#include <string>
#include <unordered_map>
#include <list>
#include <vector>

#include "networkClient.h"
#include "topic.h"
#include "nodeTopic.h"

namespace rintpc {

typedef void (*TopicListenerCallback)(const char *buffer, unsigned int length);

class TopicPublisher;

class Node{
public:
    Node(const std::string &name);
    ~Node();

    bool listenTopic(const std::string &name, TopicListenerCallback callback);
    bool shouldStop();
    TopicPublisher& advertiseTopic(const std::string &topic);
    void singleSpin();
    void spin();
    
    /* SHOULD ONLY BE CALLED BY PUBLISHER */
    bool pushTopicMessage(const TopicMessage &message);

private:
    /* ATTRIBS */
    std::string name;
    std::unordered_map<std::string, TopicListenerCallback> listeners;
    std::list<TopicMessage> messagePublishQueue;
    std::vector<TopicPublisher> publishers;

    Client client;
    bool running = true;
};

}

#endif //RINTPC_NODE_H