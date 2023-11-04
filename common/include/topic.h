#ifndef RINTPC_TOPIC_H
#define RINTPC_TOPIC_H

#include <cstdint>

namespace rintpc{

constexpr unsigned int TOPIC_NAME_SIZE = 32;
constexpr unsigned int TOPIC_MESSAGE_SIZE = 2048;

struct TopicMessage{
    char name[TOPIC_NAME_SIZE];
    uint16_t length;
    char message[TOPIC_MESSAGE_SIZE];
};/* STRUCTURE IS PACKED */

};

#endif //RINTPC_TOPIC_H