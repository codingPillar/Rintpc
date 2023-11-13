#include <iostream>

#include "constants.h"
#include "mconstants.h"
#include "network.h"
#include "networkServer.h"
#include "topicServer.h"
#include "topic.h"

using namespace std;
using namespace rintpc;

int main(int argc, char **argv){
    cout << "HOLLA RINTPC" << endl;

    cout << endl;
    cout << "|===\\  || ||   || ======== ||====\\  //====  " << endl;
    cout << "|   |  || ||\\  ||    ||    ||    |  ||      " << endl;
    cout << "|===/  || || \\ ||    ||    ||====/  ||      " << endl;
    cout << "|\\\\    || ||  \\||    ||    ||       ||      " << endl;
    cout << "| \\\\   || ||   ||    ||    ||       \\\\====" << endl;
    cout << endl;

    cout << "VERSION: " << RINTPC_MASTER_MAJOR_VERSION << "." << RINTPC_MASTER_MINOR_VERSION << endl;

    TopicServer server(MASTER_IP, MASTER_PORT);

    cout << "SERVER LISTENING ON: " << formatIP(MASTER_IP, false) << ":" << MASTER_PORT << endl;
    server.listen();

    return 0;
}