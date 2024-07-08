#include "db.h"
#include "../lib/json.hpp"
#include <fstream>
#include <iostream>
#include <regex>

KeyValueDatabase::KeyValueDatabase(const std::string &name)
{
    db_name = name;
}

void KeyValueDatabase::set(const std::string &key, const nlohmann::json &value)
{
    data[key] = value;
}

void KeyValueDatabase::get(const std::string &key) const
{
    auto it = data.find(key);
    if (it != data.end())
    {
        std::cout << it->second;
    }
    else
    {
        std::cerr << "Key " << key << " not found.";
    }
}

void KeyValueDatabase::del(const std::string &key)
{
    if (!data.erase(key))
    {
        std::cerr << "Key " << key << " not found.";
    }
}

void KeyValueDatabase::clear()
{
    data.clear();
}

void KeyValueDatabase::keys(const std::string &pattern) const
{
    std::regex regex(pattern);
    nlohmann::json result = nlohmann::json::array();
    for (const auto &pair : data)
    {
        if (std::regex_search(pair.first, regex))
        {
            result.push_back(pair.first);
        }
    }
    std::cout << result.dump();
}

void KeyValueDatabase::dump(std::ostream &os) const
{
    nlohmann::json j(data);
    os << j.dump(2) << std::endl;
}

void KeyValueDatabase::load(std::istream &is)
{
    nlohmann::json j;
    is >> j;
    data = j.get<std::unordered_map<std::string, nlohmann::json>>();
}