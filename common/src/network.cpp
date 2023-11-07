#include <network.h>

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

}