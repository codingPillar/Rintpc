#include <cstdint>
#include <cstring>

#include "nodeTopic.h"
#include "topic.h"
#include "node.h"

using namespace std;
using namespace rintpc;

/* class TopicPublisher */
TopicPublisher::TopicPublisher(const std::string &name, Node &node): name(name), node(node) {}

bool TopicPublisher::publish(const char *message, unsigned int length){
    struct TopicMessage topicMessage = {.length = (uint16_t)length};
    strcpy(topicMessage.name, this->name.c_str());
    memcpy(topicMessage.message, message, length);
    topicMessage.type = PUBLISH_MESSAGE_T;
    return this->node.pushTopicMessage(topicMessage);
}

