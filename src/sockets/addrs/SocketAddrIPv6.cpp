#include "sockets.h"
#include <arpa/inet.h>
#include <system_error>
#include <cerrno>
#include <cstring>

SocketAddrIPv6::SocketAddrIPv6(const char* ip_addr, int port) {
    if (inet_pton(AF_INET6, ip_addr, &this->s_in6.sin6_addr) < 1) {
        throw std::system_error(errno, std::generic_category(), "inet_pton error in SocketAddrIPv6");
    }
    this->s_in6.sin6_port = htons(port);
    this->s_in6.sin6_family = AF_INET6;
}

SocketAddrIPv6::SocketAddrIPv6(in_port_t bin_port) {
    this->s_in6.sin6_family = AF_INET6;
    this->s_in6.sin6_port = bin_port;
    this->s_in6.sin6_addr = in6addr_any;
}

Socket& SocketAddrIPv6::accept(const Socket &socket) const {
    return socket.visit(*this);
}

const sockaddr* SocketAddrIPv6::get_sockaddr_ptr() const {
    return (sockaddr*)&(this->s_in6);
}

sockaddr* SocketAddrIPv6::get_sockaddr_ptr_mod() {
    return (sockaddr*)&(this->s_in6);
}

size_t SocketAddrIPv6::get_sockaddr_size() const {
    return sizeof(this->s_in6);
}

in_port_t SocketAddrIPv6::get_port() const {
    return this->s_in6.sin6_port;
}

in6_addr SocketAddrIPv6::get_addr() const {
    return this->s_in6.sin6_addr;
}