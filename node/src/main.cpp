#include <iostream>
#include <netinet/in.h>

#include "node.h"

using namespace std;
using namespace rintpc;

int main(){
    cout << "NODE START" << endl;
    Node node{"MAIN"};

    TopicPublisher &publisher = node.advertiseTopic("MAP");
    publisher.publish("HOLLA", 6);

    node.spin();
    return 0;
}