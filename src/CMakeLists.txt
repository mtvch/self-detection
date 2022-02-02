cmake_minimum_required(VERSION 3.16.3)

project(lab1)

#add_compile_options(-g -O0)

include_directories(clargs)
include_directories(sockets)
include_directories(storage)


set(INCLUDE_SOURCE_FILES
    storage/Storage.cpp
    storage/ProgramSchema.cpp
    clargs/CLArgsParser.cpp
    sockets/Socket.cpp
    sockets/addrs/SocketAddr.cpp
    sockets/addrs/SocketAddrIPv4.cpp
    sockets/addrs/SocketAddrIPv6.cpp
    sockets/receiving_sockets/ReceivingSocket.cpp
    sockets/receiving_sockets/ReceivingSocketIPv4.cpp
    sockets/receiving_sockets/ReceivingSocketIPv6.cpp
    sockets/sending_sockets/SendingSocket.cpp
    sockets/sending_sockets/SendingSocketIPv4.cpp
    sockets/sending_sockets/SendingSocketIPv6.cpp
    )

add_executable(${PROJECT_NAME} ${INCLUDE_SOURCE_FILES} main.cpp)