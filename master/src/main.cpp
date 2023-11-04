#include <iostream>

#include "constants.h"
#include "network.h"
#include "topicServer.h"
#include "topic.h"

using namespace std;
using namespace rintpc;

class SimpleConnection: public Connection {
public:
    SimpleConnection(Server *server, int connectionFd) : Connection(server, connectionFd) {}

    virtual void onReceive(char *buffer, unsigned int length){
        cout << buffer << endl;
        this->send(buffer, length);
    }

};

class SimpleServer: public Server{
public:
    SimpleServer(uint32_t ip, uint16_t port): Server(ip, port) {}

    virtual Connection* getConnection(int connectionFd) override {
        return new SimpleConnection(this, connectionFd);
    }

    virtual void cleanConnection(Connection *connection) override{
        delete connection;
    }
};

int main(int argc, char **argv){
    cout << "HOLLA RINTPC" << endl;

    //SimpleServer server(MASTER_IP, MASTER_PORT);
    TopicServer server(MASTER_IP, MASTER_PORT);

    server.listen();

    return 0;
}