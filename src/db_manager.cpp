#include "db_manager.h"
#include "utils.h"
#include <iostream>
#include <fstream>

DatabaseManager::DatabaseManager()
{
    databases["default"] = std::make_shared<KeyValueDatabase>("default");
    currentDatabase = databases["default"];
}

void DatabaseManager::use(const std::string &dbname)
{
    if (databases.find(dbname) == databases.end())
    {
        databases[dbname] = std::make_shared<KeyValueDatabase>(dbname);
    }
    currentDatabase = databases[dbname];
}

void DatabaseManager::set(const std::string &key, const std::string &value)
{
    nlohmann::json jsonValue = try_parse_json(value);

    if (jsonValue.is_string())
    {
        std::string trimmed_value = jsonValue.get<std::string>();

        try
        {
            size_t idx;
            int intValue = std::stoi(trimmed_value, &idx);
            if (idx == trimmed_value.length())
            {
                jsonValue = intValue;
            }
            else
            {
                throw std::invalid_argument("not an integer");
            }
        }
        catch (...)
        {
        }

        if (jsonValue.is_string())
        {
            try
            {
                size_t idx;
                float floatValue = std::stof(trimmed_value, &idx);
                if (idx == trimmed_value.length())
                {
                    jsonValue = floatValue;
                }
            }
            catch (...)
            {
            }
        }
    }
    currentDatabase->set(key, jsonValue);
}

void DatabaseManager::get(const std::string &key) const
{
    currentDatabase->get(key);
}

void DatabaseManager::del(const std::string &key)
{
    currentDatabase->del(key);
}

void DatabaseManager::clear()
{
    currentDatabase->clear();
}

void DatabaseManager::keys(const std::string &pattern) const
{

    currentDatabase->keys(pattern);
}

nlohmann::json DatabaseManager::list() const
{
    nlohmann::json dbArray = nlohmann::json::array();
    for (const auto &db : databases)
    {
        dbArray.push_back(db.first);
    }
    return dbArray;
}

void DatabaseManager::dump(const std::string &dbname, const std::string &path) const
{
    auto it = databases.find(dbname);
    if (it != databases.end())
    {
        std::ofstream ofs(path);
        if (ofs)
        {
            it->second->dump(ofs);
        }
        else
        {
            std::cerr << "Failed to open file: ";
        }
    }
    else
    {
        std::cerr << "Database " << dbname << " not found.";
    }
}

void DatabaseManager::load(const std::string &dbname, const std::string &path)
{
    std::ifstream ifs(path);
    if (ifs)
    {
        databases[dbname] = std::make_shared<KeyValueDatabase>(dbname);
        databases[dbname]->load(ifs);
        currentDatabase = databases[dbname];
    }
    else
    {
        std::cerr << "Failed to open file: " << path << std::endl;
    }
}