#include <iostream>
#include <cstdio>

#include "node.h"
#include "topic.h"

using namespace std;
using namespace rintpc;

void mapTopicCallback(const char *buffer, unsigned int length){
    auto message = (TopicMessage*) buffer;
    cout << "TOPIC: " << message->name << endl;
    printf("MESSAGE: %s\n", message->message);
}

int main(){
    Node node("LISTENER");

    node.listenTopic("MAP", mapTopicCallback);

    node.spin();

    return 0;
}