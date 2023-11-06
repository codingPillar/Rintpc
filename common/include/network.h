#ifndef RINTPC_COMMON_NETWORK_H
#define RINTPC_COMMON_NETWORK_H

#include <stdint.h>

namespace rintpc {

/* VALUES ARE IN NETWORK FORMAT */
struct NodeAddress{
    uint32_t ip;
    uint16_t port;
};

}

#endif //RINTPC_COMMON_NETWORK_H