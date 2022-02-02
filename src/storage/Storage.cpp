#include "storage.h"
#include <iomanip>

void Storage::insert(const std::string& id, const std::string& ip) {
    this->entries.emplace(std::piecewise_construct, std::forward_as_tuple(id), std::forward_as_tuple(id, ip));
}

bool Storage::exists(const std::string& id) const {
    if (this->entries.find(id) == this->entries.end()) {
        return false;
    }
    return true;
}

void Storage::update_last_seen_time(const std::string& id) {
    std::unordered_map<std::string, ProgramSchema>::iterator  itr = this->entries.find(id);
    if (itr != this->entries.end()) {
        itr->second.update_last_seen_time();
        return;
    }
    throw std::invalid_argument("Program with such id does not exist");
}


void Storage::print_entries() const {
    std::cout << std::left << std::setw(10) << "ID";
    std::cout << std::left << std::setw(30) << "LAST SEEN";
    std::cout << std::left << std::setw(30) << "IP" << std::endl;
    std::unordered_map<std::string, ProgramSchema>::const_iterator itr;
    for (itr = this->entries.begin(); itr != this->entries.end(); itr++) {
        std::cout << itr->second << std::endl;
    }
}

int Storage::delete_outdated() {
    int deleted_counter = 0;
    std::unordered_map<std::string, ProgramSchema>::const_iterator itr;
    for (itr = this->entries.begin(); itr != this->entries.end(); itr++) {
        if (itr->second.is_outdated()) {
            this->entries.erase(itr);
            deleted_counter++;
        }
    }

    return deleted_counter;
}