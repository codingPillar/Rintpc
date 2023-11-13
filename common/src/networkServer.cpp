#include <array>
#include <iostream>
#include <cstdlib>
#include <unistd.h>

#include <sys/socket.h>
#include <netinet/in.h>

#include "network.h"
#include "networkServer.h"

using namespace std;

namespace rintpc {

class Server;

/* CLASS Connection */
Connection::Connection(Server *server, NodeAddress remote, int connectionFd) : remote(remote), server(server),  connectionFd(connectionFd) {}

int Connection::send(char *buffer, unsigned int length){
    long int result = ::send(this->connectionFd, buffer, length, 0);
    if(result != length)
        cout << "COULD NOT SEND ENTIRE MESSAGE, SENT: " << result << " EXPECTED: " << length << " ON FD: " << connectionFd << endl;
    return result;
}

bool Connection::dataAvailable(){
    return rintpc::dataAvailable(this->connectionFd);
}

/* CLASS Server */
Server::Server(uint32_t ip, uint16_t port) : address{ip, port}, running(true) {
    int result = 0;
    this->socketFd = socket(AF_INET, SOCK_STREAM, 0);
    sockaddr_in sockAddr = {.sin_family = AF_INET, .sin_port = htons(port),
        .sin_addr = {.s_addr = htonl(ip)}};
    result = bind(this->socketFd, (const struct sockaddr *)&sockAddr, sizeof(sockAddr));
    if(result != 0)
        cout << "COULD NOT BIND TO ADDRESS " << ip << " PORT " << port << endl;
    /* TODO, EXIT PROGRAM ON ERROR */
}

void RINTPC_BLOCKING Server::listen(){
    this->startReceiveThread();
    ::listen(socketFd, BACKLOG_SIZE);
    while(this->running){
        struct sockaddr_in client;
        unsigned int sockLength = sizeof(client);
        int connectionFd = accept(this->socketFd, (struct sockaddr*)&client, &sockLength);
        /* VERIFY THAT WE WERE ABLE TO ACCEPT CONNECTION */
        if(connectionFd < 0) continue;
        cout << "RECEIVED CONNECTION FROM: " << formatIP(client.sin_addr.s_addr) << " PORT: " << ntohs(client.sin_port) << endl;
        Connection *conn = this->getConnection({ntohl(client.sin_addr.s_addr), ntohs(client.sin_port)}, connectionFd);
        this->connections.push_back(conn);
    }
}

void Server::stop(){
    this->running = false;
}

void Server::startReceiveThread(){
    auto threadMain = [this](){
        cout << "STARTED SERVER RECEIVE THREAD" << endl;
        array<char, SOCK_RCV_BUFF_MAX_SIZE> buffer;
        while(this->running){
            for(auto connection : this->connections){
                if(!connection->dataAvailable()) continue;
                unsigned int length = recv(connection->connectionFd, buffer.data(), SOCK_RCV_BUFF_MAX_SIZE, 0);
                if(length > 0)
                    connection->onReceive(buffer.data(), length, data);
            }
        }
    };
    this->thread = new std::thread(threadMain);
}

void Server::cleanReceiveThread(){
    if(!this->thread) return;
    this->thread->join();
    delete this->thread;
}


};