#ifndef RINTPC_TOPIC_HANDLER
#define RINTPC_TOPIC_HANDLER

#include <unordered_map>
#include <list>
#include <string>
#include <mutex>
#include <utility>
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
    void addTopicListener(const std::string &name, Connection *listener);
    
    std::vector<std::string> getTopics();
    std::pair<TopicMessage, std::vector<Connection*>> popTopicMessage(const std::string &name);

    /* UNIPLEMENTED */
    bool removeTopicListener(const std::string &name, const struct NodeAddress &listener);

private:
    TopicHandler();
    void lockBoth();
    void unlockBoth();

    static TopicHandler instance;

    /* COULD BE MANIPULATED FROM MULTIPLE THREADS */
    std::unordered_map<std::string, std::list<TopicMessage>> messageQueue;
    std::mutex messageMut;

    /* COULD BE MANIPULATED FROM MULTIPLE THREADS */
    std::unordered_map<std::string, std::vector<Connection*>> topicListeners;
    std::mutex listenersMut;
};

}

#endif //RINTPC_TOPIC_HANDLER