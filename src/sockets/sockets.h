#ifndef SOCKETS_H
#define SOCKETS_H

#include <string>
#include <netinet/in.h>

class SocketAddr;
class SocketAddrIPv4;
class SocketAddrIPv6;
class Socket;
class SendingSocket;
class SendingSocketIPv4;
class SendingSocketIPv6;
class ReceivingSocket;
class ReceivingSocketIPv4;
class ReceivingSocketIPv6;

class SocketAddr {
    private:
        virtual Socket& accept(const Socket &socket) const = 0;
        virtual sockaddr* get_sockaddr_ptr_mod() = 0;
    public:
        virtual const sockaddr* get_sockaddr_ptr() const = 0;
        virtual size_t get_sockaddr_size() const = 0;
        static SocketAddr& create(const std::string &addr_string, const std::string &port_string);
        friend class SendingSocket;
        friend class ReceivingSocket;
};

class SocketAddrIPv4 : SocketAddr {
    private:
        SocketAddrIPv4(const char *ip_addr, int port);
        sockaddr_in s_in;
        virtual Socket& accept(const Socket &socket) const override;
        virtual sockaddr* get_sockaddr_ptr_mod() override;
    public:
        SocketAddrIPv4(in_port_t bin_port);
        SocketAddrIPv4() {};
        virtual const sockaddr* get_sockaddr_ptr() const override;
        virtual size_t get_sockaddr_size() const override;
        in_port_t get_port() const;
        in_addr get_addr() const;
        friend class SocketAddr;
        friend class ReceivingSocketIPv4;
};

class SocketAddrIPv6 : SocketAddr {
    private:
        SocketAddrIPv6(const char *ip_addr, int port);
        sockaddr_in6 s_in6;
        virtual sockaddr* get_sockaddr_ptr_mod() override;
        virtual Socket& accept(const Socket &socket) const override;
    public:
        SocketAddrIPv6(in_port_t bin_port);
        SocketAddrIPv6() {};
        virtual const sockaddr* get_sockaddr_ptr() const override;
        virtual size_t get_sockaddr_size() const override;
        in_port_t get_port() const;
        in6_addr get_addr() const;
        friend class SocketAddr;
        friend class ReceivingSocketIPv6;
};

class Socket {
    private:
        virtual Socket& visit(const SocketAddrIPv4 &socket_addr) const = 0;
        virtual Socket& visit(const SocketAddrIPv6 &socket_addr) const = 0;
    protected:
        int sd;
    public:
        ~Socket();
        friend class SocketAddrIPv4;
        friend class SocketAddrIPv6;
}; 

class SendingSocket : public Socket {
    private:
        virtual Socket& visit(const SocketAddrIPv4 &socket_addr) const override;
        virtual Socket& visit(const SocketAddrIPv6 &socket_addr) const override;
    protected:
        SendingSocket() {};
    public:
        static SendingSocket& create(const SocketAddr &socket_addr);
        void send(const std::string &msg, const SocketAddr &addr);
};

class SendingSocketIPv4 : SendingSocket {
    private:
        SendingSocketIPv4();
    public:
        friend class SendingSocket;
};

class SendingSocketIPv6 : SendingSocket {
    private:

        SendingSocketIPv6();
    public:
        friend class SendingSocket;
};

class ReceivingSocket : public Socket {
    private:
        virtual Socket& visit(const SocketAddrIPv4 &socket_addr) const override;
        virtual Socket& visit(const SocketAddrIPv6 &socket_addr) const override;
    protected:
        std::string last_from_ip_string = "";
        char buff[7];
        ReceivingSocket() {};
    public:
        const std::string& get_last_from_ip_string() const;
        static ReceivingSocket& create(const SocketAddr& socket_addr);
        virtual const std::string& receive() = 0;
};

class ReceivingSocketIPv4 : public ReceivingSocket {
    private:
        void make_reusable();
        void bind_to_group_port(const SocketAddrIPv4 &group_addr);
        void join_group(const SocketAddrIPv4 &group_addr);
        ReceivingSocketIPv4(const SocketAddrIPv4 &socket_addr);
        ReceivingSocketIPv4() {};
    public:
        virtual const std::string& receive() override;
        friend class ReceivingSocket;
};

class ReceivingSocketIPv6 : public ReceivingSocket {
    private:
        void make_reusable();
        void bind_to_group_port(const SocketAddrIPv6 &group_addr);
        void join_group(const SocketAddrIPv6 &group_addr);
        ReceivingSocketIPv6(const SocketAddrIPv6 &socket_addr);
        ReceivingSocketIPv6() {};
    public:
        virtual const std::string& receive() override;
        friend class ReceivingSocket;
};

#endif