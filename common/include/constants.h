#ifndef RINTPC_COMMON_CONSTANTS_H
#define RINTPC_COMMON_CONSTANTS_H

#include <stdint.h>

/* TO INDICATE THAT A CERTAIN FUNCTION IS BLOCKING */
#define RINTPC_BLOCKING

namespace rintpc {

constexpr unsigned int BACKLOG_SIZE = 256;

constexpr unsigned int SOCK_RCV_BUFF_MAX_SIZE = 2048;

constexpr unsigned int LOCAL_HOST_IP = (127 << (8 * 3)) | 1;

constexpr uint16_t MASTER_PORT = 50101;
/* MASTER IP 127.0.0.1 */
constexpr uint32_t MASTER_IP = LOCAL_HOST_IP;

}

#endif //RINTPC_COMMON_CONSTANTS_H