#include <network.h>

std::string rintpc::formatIP(uint32_t ip, bool networkFormat){
    char buffer[16];
    unsigned int counter = 0;
    if(networkFormat) ip = ntohl(ip);
    for(unsigned int i = 0; i < sizeof(uint32_t); i++)
        counter += std::sprintf(&buffer[counter], (i < sizeof(uint32_t) - 1) ? "%d." : "%d", (ip >> (8 * (sizeof(uint32_t) - i - 1))) & 0x00FF);
    return std::string(buffer);
}