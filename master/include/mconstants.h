#ifndef RINTPC_CONSTANTS_H
#define RINTPC_CONSTANTS_H

#include <cstdint>

namespace rintpc {

constexpr uint16_t MASTER_PORT = 50101;
/* MASTER IP 127.0.0.1 */
constexpr uint32_t MASTER_IP = (127 << (8 * 3)) | 1;

constexpr unsigned int BACKLOG_SIZE = 256;

constexpr unsigned int SOCK_RCV_BUFF_MAX_SIZE = 1024;
};

#endif //RINTPC_CONSTANTS_H