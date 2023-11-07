#ifndef RINTPC_COMMON_NETWORK_H
#define RINTPC_COMMON_NETWORK_H

#include <cstdint>
#include <netinet/in.h>
#include <string>

namespace rintpc {

/* VALUES ARE IN NETWORK FORMAT */
struct NodeAddress{
    uint32_t ip;
    uint16_t port;
};

std::string formatIP(uint32_t ip, bool networkFormat = true);

}

#endif //RINTPC_COMMON_NETWORK_H