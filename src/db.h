#ifndef DB_H
#define DB_H

#include "../lib/json.hpp"

#include <iostream>
#include <fstream>
#include <unordered_map>
#include <string>
#include <regex>

class KeyValueDatabase
{
public:
    KeyValueDatabase(const std::string &name = "");
    void set(const std::string &key, const nlohmann::json &value);
    void get(const std::string &key) const;
    void del(const std::string &key);
    void clear();
    void keys(const std::string &pattern) const;
    void dump(std::ostream &os) const;
    void load(std::istream &is);

private:
    std::unordered_map<std::string, nlohmann::json> data;
    std::string db_name;
};

#endif