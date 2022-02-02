#include "sockets.h"
#include <system_error>
#include <cerrno>
#include <cstring>


ReceivingSocket& ReceivingSocket::create(const SocketAddr& socket_addr) {
    ReceivingSocketIPv4 receiving_socket; // dont matter if ipv4 or ipv6
    return dynamic_cast<ReceivingSocket&>(socket_addr.accept(receiving_socket));
}

Socket& ReceivingSocket::visit(const SocketAddrIPv4& addr) const {
  static ReceivingSocketIPv4 socket(addr);
  return socket;
}

Socket& ReceivingSocket::visit(const SocketAddrIPv6 &addr) const {
  static ReceivingSocketIPv6 socket(addr);
  return socket;
}

const std::string& ReceivingSocket::get_last_from_ip_string() const {
  if (this->last_from_ip_string.empty()) {
    throw std::system_error(errno, std::generic_category(), "Error getting last from ip string");
  }
  return this->last_from_ip_string;
}
