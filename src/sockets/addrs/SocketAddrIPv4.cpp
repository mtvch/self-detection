#include "sockets.h"
#include <arpa/inet.h>

SocketAddrIPv4::SocketAddrIPv4(const char *ip_addr, int port) {
    this->s_in.sin_addr.s_addr = inet_addr(ip_addr);
    this->s_in.sin_port = htons(port);
    this->s_in.sin_family = AF_INET;
}

SocketAddrIPv4::SocketAddrIPv4(in_port_t bin_port) {
    this->s_in.sin_family = AF_INET;
    this->s_in.sin_port = bin_port;
    this->s_in.sin_addr.s_addr = htonl(INADDR_ANY);
}

Socket& SocketAddrIPv4::accept(const Socket &socket) const {
    return socket.visit(*this);
}

const sockaddr* SocketAddrIPv4::get_sockaddr_ptr() const {
    return (sockaddr*)&(this->s_in);
}

sockaddr* SocketAddrIPv4::get_sockaddr_ptr_mod() {
    return (sockaddr*)&(this->s_in);
}

size_t SocketAddrIPv4::get_sockaddr_size() const {
    return sizeof(this->s_in);
}

in_port_t SocketAddrIPv4::get_port() const {
    return this->s_in.sin_port;
}

in_addr SocketAddrIPv4::get_addr() const {
    return this->s_in.sin_addr;
}