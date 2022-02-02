#include <regex>
#include <stdlib.h>
#include <stdexcept>
#include "sockets.h"


SocketAddr& SocketAddr::create(const std::string &addr_string, const std::string &port_string) {
    std::regex addr_reg("^[\\d]{1,3}\\.[\\d]{1,3}\\.[\\d]{1,3}\\.[\\d]{1,3}$");
    std::regex port_reg("^[\\d]{1,5}$");
    std::regex_match(addr_string, addr_reg);
    if (std::regex_match(addr_string, addr_reg)) {
        const char* ip_addr = addr_string.c_str();
        int port = std::stoi(port_string);
        static SocketAddrIPv4 socket_addr(ip_addr, port);
        return socket_addr;
    }

    addr_reg.assign("^[\\dABCDEFabcdef:]+$"); // TODO: correct regex
    if (std::regex_match(addr_string, addr_reg)) {
        const char* ip_addr = addr_string.c_str();
        int port = std::stoi(port_string);
        static SocketAddrIPv6 socket_addr(ip_addr, port);
        return socket_addr;
    }

    throw std::invalid_argument("Invalid socket addr");
}
