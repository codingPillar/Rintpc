#include <iostream>
#include <netinet/in.h>

#include "constants.h"
#include "network.h"
#include "networkClient.h"

using namespace std;
using namespace rintpc;

int main(){
    cout << "NODE START" << endl;

    struct NodeAddress server = {.ip = htonl(MASTER_IP), .port = htons(MASTER_PORT)};
    Client client{server};

    unsigned int counter = 0;
    while(counter < 10){
        client.send("HOLLA\n", 6);
        counter++;
    }

    return 0;
}