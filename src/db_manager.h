#ifndef DB_MANAGER_H
#define DB_MANAGER_H

#include "db.h"
#include "../lib/json.hpp"
#include <unordered_map>
#include <string>
#include <memory>

class DatabaseManager
{
public:
    DatabaseManager();
    void use(const std::string &dbname);
    void set(const std::string &key, const std::string &value);
    void get(const std::string &key) const;
    void del(const std::string &key);
    void clear();
    void keys(const std::string &pattern) const;
    nlohmann::json list() const;
    void dump(const std::string &dbname, const std::string &path) const;
    void load(const std::string &dbname, const std::string &path);

private:
    std::unordered_map<std::string, std::shared_ptr<KeyValueDatabase>> databases;
    std::shared_ptr<KeyValueDatabase> currentDatabase;
};

#endif