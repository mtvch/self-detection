#include "sockets.h"
#include <sys/socket.h>
#include <system_error>
#include <cerrno>
#include <cstring>
#include <arpa/inet.h>

ReceivingSocketIPv4::ReceivingSocketIPv4(const SocketAddrIPv4 &group_addr) {
    this->sd = socket(AF_INET, SOCK_DGRAM, 0);
    if (this->sd == -1) {
        throw std::system_error(errno, std::generic_category(), "Error creating socket");
    }
    make_reusable();
    bind_to_group_port(group_addr);
    join_group(group_addr);
}

void ReceivingSocketIPv4::make_reusable() {
    int reuse=1;

    if (setsockopt(this->sd, SOL_SOCKET, SO_REUSEADDR, (char *)&reuse, sizeof(reuse)) < 0) {
        throw std::system_error(errno, std::generic_category(), "Error while setting reusable");
    }
}

void ReceivingSocketIPv4::bind_to_group_port(const SocketAddrIPv4 &group_addr) {
    SocketAddrIPv4 local_addr(group_addr.get_port());

    if (bind(this->sd, local_addr.get_sockaddr_ptr(), local_addr.get_sockaddr_size()) < 0) {
        throw std::system_error(errno, std::generic_category(), "Error binding to port");
    }
}

void ReceivingSocketIPv4::join_group(const SocketAddrIPv4 &group_addr) {
    // TODO:
    // mreq to class
    ip_mreq mr;
    mr.imr_multiaddr = group_addr.get_addr();
    mr.imr_interface.s_addr = htonl(INADDR_ANY);
    if (setsockopt(this->sd, IPPROTO_IP, IP_ADD_MEMBERSHIP, (char *)&mr, sizeof(mr)) < 0) {
        throw std::system_error(errno, std::generic_category(), "Error joining group");
    }
}

const std::string& ReceivingSocketIPv4::receive() {
    SocketAddrIPv4 client_addr;
    socklen_t from_len = client_addr.get_sockaddr_size();
    if (recvfrom(this->sd, this->buff, sizeof(this->buff), MSG_WAITALL, client_addr.get_sockaddr_ptr_mod(), &from_len) < 0) {
        throw std::system_error(errno, std::generic_category(), "Error receiving");
    }

    char host[INET_ADDRSTRLEN];
    in_addr addr = client_addr.get_addr();
    if (inet_ntop(AF_INET, &addr, host, INET_ADDRSTRLEN) < 0) {
        throw std::system_error(errno, std::generic_category(), "inet_ntop error");
    }

    this->last_from_ip_string.assign(host);

    // if (read(this->sd, this->buff, sizeof(this->buff)) < 0) {
    //     throw std::system_error(errno, std::generic_category(), "Error receiving");
    // }
    static std::string msg; // why strange things happen with simple constructor?
    msg.assign(this->buff);
    return msg;
}