#include <iostream>
#include <netinet/in.h>

#include "node.h"
#include "clock.h"

using namespace std;
using namespace rintpc;

int main(){
    cout << "NODE START" << endl;
    Node node{"MAIN"};

    TopicPublisher &publisher = node.advertiseTopic("MAP");
    (void) publisher;

    Clock clock(1); /* 1 Hz CLOCK */
    while(!node.shouldStop()){
        clock.sleep();
        cout << "HOLLA" << endl;
        publisher.publish("HOLLA", 6);
        node.singleSpin();
    }
    
    return 0;
}