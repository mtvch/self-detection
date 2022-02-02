#ifndef STORAGE_H
#define STORAGE_H

#include <string>
#include <unordered_map>
#include <ctime>
#include <iostream>

#define LIVE_TIME 2 // время жизни записи без продления в секундах

class ProgramSchema {
    private:
        const std::string id;
        const std::string ip;
        time_t last_seen_time;
    public:
        const std::string& get_id() const;
        ProgramSchema() = delete;
        ProgramSchema(const std::string& id, const std::string& ip);
        bool is_outdated() const;
        friend std::ostream& operator<<(std::ostream &out, const ProgramSchema &schema);
        void update_last_seen_time();
};

class Storage {
    private:
        std::unordered_map<std::string, ProgramSchema> entries;
    public:
        bool exists(const std::string& id) const;
        void insert(const std::string& id, const std::string& ip);
        void update_last_seen_time(const std::string& id);
        int delete_outdated();
        void print_entries() const;
};

#endif