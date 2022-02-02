#include "clargs.h"
#include "sockets.h"
#include "storage.h"
#include <iostream>
#include <random>
#include <unistd.h>

#define DEFAULT_MULTICAST_GROUP_ADDR "239.0.0.1"
#define DEFAULT_MULTICAST_GROUP_PORT "4321"

void init_group_attrs(const CLArgsParser &parser, std::string &group_addr_string, std::string& group_port_string);
const std::string& gen_id();

int main(int argc, char **argv) {
    CLArgsParser parser(argc, argv);
    std::string group_addr_string;
    std::string group_port_string;
    init_group_attrs(parser, group_addr_string, group_port_string);
    SocketAddr &multicast_group_addr = SocketAddr::create(group_addr_string, group_port_string);
    SendingSocket sending_socket = SendingSocket::create(multicast_group_addr);
    ReceivingSocket &receiving_socket = ReceivingSocket::create(multicast_group_addr);

    const std::string my_id = gen_id();
    std::cout << "My ID: " << my_id << std::endl;
    std::cout << std::endl;

    Storage storage;

    while(true) {
        sending_socket.send(my_id, multicast_group_addr);
        std::string some_id;
        do {
            some_id.assign(receiving_socket.receive());
        } while (some_id == my_id);
        int deleted_counter = storage.delete_outdated();
        if (storage.exists(some_id)) {
            storage.update_last_seen_time(some_id);
            if (deleted_counter) {
                storage.print_entries();
            }
            continue;
        }
        storage.insert(some_id, receiving_socket.get_last_from_ip_string());
        storage.print_entries();
        std::cout << std::endl;
    }

    return 0;
}

void init_group_attrs(const CLArgsParser &parser, std::string &group_addr_string, std::string& group_port_string) {
    if (parser.option_exists("-a")) {
        group_addr_string.assign(parser.get_parameter("-a"));
    } else {
        group_addr_string.assign(DEFAULT_MULTICAST_GROUP_ADDR);
    }
    if (parser.option_exists("-p")) {
        group_port_string.assign(parser.get_parameter("-p"));
    } else {
        group_port_string.assign(DEFAULT_MULTICAST_GROUP_PORT);
    }
}

const std::string& gen_id() {
    std::random_device dev;
    std::mt19937 rng(dev());
    std::uniform_int_distribution<std::mt19937::result_type> dist(100000, 999999);
    static std::string id = std::to_string(dist(rng));
    return id;
}