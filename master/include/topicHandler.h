#ifndef RINTPC_TOPIC_HANDLER
#define RINTPC_TOPIC_HANDLER

#include <unordered_map>
#include <list>
#include <string>
#include <mutex>
#include <vector>

#include "topic.h"
#include "network.h"
#include "networkServer.h"

namespace rintpc {

/* SIGLETON CLASS */
class TopicHandler{
public:
    static TopicHandler* getTopicHandler();

    bool registerTopic(const std::string &name);
    bool pushTopicMessage(const struct TopicMessage *topicMessage);
    void addTopicListener(const std::string &name, const struct NodeAddress &listener);

    /* UNIPLEMENTED */
    std::pair<TopicMessage, std::vector<NodeAddress>> popTopicMessage(const std::string &name);
    bool removeTopicListener(const std::string &name, const struct NodeAddress &listener);

private:
    TopicHandler();
    void lockBoth();
    void unlockBoth();

    static TopicHandler instance;

    /* COULD BE MANIPULATED FROM MULTIPLE THREADS */
    std::unordered_map<std::string, std::list<TopicMessage>> messageQueue;
    std::mutex messageMut;

    /* FOR NOW ONLY ONE WRITER PER TOPIC */
    /* std::unordered_map<std::string, std::vector<NodeAddress>> topicWriters; */
    /* COULD BE MANIPULATED FROM MULTIPLE THREADS */
    std::unordered_map<std::string, std::vector<NodeAddress>> topicListeners;
    std::mutex listenersMut;
};

}

#endif //RINTPC_TOPIC_HANDLER