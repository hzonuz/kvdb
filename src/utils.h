#ifndef UTILS_H
#define UTILS_H

#include <iostream>
#include <sstream>
#include <vector>
#include <string>

#include "db.h"
#include "db_manager.h"

void printUsage();

void executeCommand(DatabaseManager& dbManager, const std::string& command, const std::vector<std::string>& args);

nlohmann::json try_parse_json(const std::string& value);

#endif