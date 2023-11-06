#ifndef RINTPC_COMMON_CONSTANTS_H
#define RINTPC_COMMON_CONSTANTS_H

/* TO INDICATE THAT A CERTAIN FUNCTION IS BLOCKING */
#define RINTPC_BLOCKING

namespace rintpc {

constexpr unsigned int BACKLOG_SIZE = 256;

constexpr unsigned int SOCK_RCV_BUFF_MAX_SIZE = 1024;

constexpr unsigned int LOCAL_HOST_IP = (127 << (8 * 3)) | 1;
}

#endif //RINTPC_COMMON_CONSTANTS_H