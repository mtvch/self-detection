#include "storage.h"
#include <iomanip>

ProgramSchema::ProgramSchema(const std::string& id, const std::string& ip) : id(id), ip(ip) {
    update_last_seen_time();
}

void ProgramSchema::update_last_seen_time() {
    this->last_seen_time = std::time(nullptr);
}

bool ProgramSchema::is_outdated() const {
    if (std::difftime(std::time(nullptr), this->last_seen_time) > LIVE_TIME) {
        return true;
    }
    return false;
}

std::ostream& operator<<(std::ostream &out, const ProgramSchema &schema) {
    std::tm * ptm = std::localtime(&schema.last_seen_time);
    char buffer[32];
    std::strftime(buffer, 32, "%a, %d.%m.%Y %H:%M:%S", ptm);  
    out << std::left << std::setw(10) << schema.id;
    out << std::left << std::setw(30) << buffer;
    out << std::left << std::setw(30) << schema.ip;
    return out;
}

const std::string& ProgramSchema::get_id() const {
    return this->id;
}