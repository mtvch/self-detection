#include <system_error>
#include <cerrno>
#include <cstring>
#include "sockets.h"

SendingSocket& SendingSocket::create(const SocketAddr &socket_addr) {
  SendingSocket sending_socket;
  return dynamic_cast<SendingSocket&>(socket_addr.accept(sending_socket));
}

Socket& SendingSocket::visit(const SocketAddrIPv4&) const {
  static SendingSocketIPv4 socket;
  return socket;
}

Socket& SendingSocket::visit(const SocketAddrIPv6&) const {
  static SendingSocketIPv6 socket;
  return socket;
}

void SendingSocket::send(const std::string &msg, const SocketAddr &addr) {
    if (sendto(this->sd, msg.c_str(), msg.size(), 0, addr.get_sockaddr_ptr(), addr.get_sockaddr_size()) < 0) {
        throw std::system_error(errno, std::generic_category(), "Error sending");
    }
}
