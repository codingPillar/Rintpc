#ifndef RINTPC_NODE_TOPIC_H
#define RINTPC_NODE_TOPIC_H

#include <string>

#include "topic.h"
#include "networkClient.h"

namespace rintpc {

class Node;
bool pushTopicMessage(const TopicMessage &message);


class TopicPublisher{
public:
    TopicPublisher(const std::string &name, Node &node);

    bool publish(const char *message, unsigned int length);

private:
    std::string name;
    Node &node;
};

}

#endif //RINTPC_NODE_TOPIC_H