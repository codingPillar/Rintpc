#include <network.h>
#include <poll.h>

using namespace std;

namespace rintpc {

extern const struct NodeAddress MASTER_NODE_ADDRESS = {.ip = htonl(MASTER_IP), .port = htons(MASTER_PORT)};

string formatIP(uint32_t ip, bool networkFormat){
    char buffer[16];
    unsigned int counter = 0;
    if(networkFormat) ip = ntohl(ip);
    for(unsigned int i = 0; i < sizeof(uint32_t); i++)
        counter += sprintf(&buffer[counter], (i < sizeof(uint32_t) - 1) ? "%d." : "%d", (ip >> (8 * (sizeof(uint32_t) - i - 1))) & 0x00FF);
    return string(buffer);
}

bool dataAvailable(int fd){
    struct pollfd pollfd = {.fd = fd, .events = POLLIN};
    /* NON-BLOCKING AND ONLY ONE FILE DESCRIPTOR */
    int result = poll(&pollfd, 1, 0);
    if(result < 0) return false;
    return (pollfd.revents & POLLIN) != 0;
}

}