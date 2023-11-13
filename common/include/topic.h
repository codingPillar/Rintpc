#ifndef RINTPC_TOPIC_H
#define RINTPC_TOPIC_H

#include <cstdint>

#include "constants.h"

namespace rintpc{

constexpr unsigned int TOPIC_NAME_SIZE = 32;
constexpr unsigned int TOPIC_MESSAGE_SIZE = SOCK_RCV_BUFF_MAX_SIZE / 2;

enum TOPIC_MESSAGE_TYPE{
    REGISTER_TOPIC_T,
    PUBLISH_MESSAGE_T
};

struct TopicMessage{
    char name[TOPIC_NAME_SIZE];
    enum TOPIC_MESSAGE_TYPE type; 
    uint16_t length;
    char message[TOPIC_MESSAGE_SIZE];
};/* STRUCTURE IS PACKED */

};

#endif //RINTPC_TOPIC_H