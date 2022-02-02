#include "sockets.h"
#include <system_error>
#include <cerrno>
#include <cstring>

SendingSocketIPv4::SendingSocketIPv4() {
    this->sd = socket(AF_INET, SOCK_DGRAM, 0);
    if (this->sd == -1) {
        throw std::system_error(errno, std::generic_category(), "Error creating socket");
    }
    //disable_loopback();
    //set_interface();
}

// void SendingSocketIPv4::disable_loopback() {
//     u_char loop = 0;

//     if (setsockopt(this->sd, IPPROTO_IP, IP_MULTICAST_LOOP, &loop, sizeof(loop)) < 0) {
//       throw std::system_error(errno, std::generic_category(), "Error disabling loopback");
//     }
// }

// void SendingSocketIPv4::set_interface() {
//   in_addr local_interface;
//   local_interface.s_addr = htonl(INADDR_ANY);
//   if (setsockopt(this->sd, IPPROTO_IP, IP_MULTICAST_IF, (char*)&local_interface, sizeof(local_interface)) < 0) {
//     throw std::system_error(errno, std::generic_category(), std::strerror(errno));
//   }
// }
