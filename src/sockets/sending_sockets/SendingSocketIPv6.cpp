#include "sockets.h"
#include <system_error>
#include <cerrno>
#include <cstring>

SendingSocketIPv6::SendingSocketIPv6() {
    this->sd = socket(AF_INET6, SOCK_DGRAM, 0);
    if (this->sd == -1) {
        throw std::system_error(errno, std::generic_category(), "Error creating socket");
    }
    //disable_loopback();
}

// void SendingSocketIPv6::disable_loopback() {
//     u_char loop = 0;

//     if (setsockopt(this->sd, IPPROTO_IPV6, IPV6_MULTICAST_LOOP, &loop, sizeof(loop)) < 0) {
//       throw std::system_error(errno, std::generic_category(), "Error disabling loopback");
//     }
// }
