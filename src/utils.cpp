#include "utils.h"

void printUsage()
{
    std::cout << "\n----------------------------------------------------\n";
    std::cout << "Usage:\n";
    std::cout << "  # set <key> <value>          - Set a key-value pair\n";
    std::cout << "  # get <key>                  - Get the value for a key\n";
    std::cout << "  # del <key>                  - Delete a key-value pair\n";
    std::cout << "  # clear                      - Clear the database\n";
    std::cout << "  # keys <regex>               - Find keys matching a regex pattern\n";
    std::cout << "  # list                       - List all databases\n";
    std::cout << "  # dump <dbname> <path>       - Dump a database to a file\n";
    std::cout << "  # load <path> <dbname>       - Load a database from a file\n";
    std::cout << "  # exit                       - Exit the program\n";
    std::cout << "----------------------------------------------------\n\n";
}

void executeCommand(DatabaseManager &dbManager, const std::string &command, const std::vector<std::string> &args)
{
    if (command == "use" && args.size() == 1)
    {
        dbManager.use(args[0]);
    }
    else if (command == "list" && args.size() == 0)
    {
        nlohmann::json dbList = dbManager.list();
        std::cout << dbList.dump();
    }
    else if (command == "get" && args.size() == 1)
    {
        dbManager.get(args[0]);
    }
    else if (command == "keys" && args.size() == 1)
    {
        dbManager.keys(args[0]);
    }
    else if (command == "del" && args.size() == 1)
    {
        dbManager.del(args[0]);
    }
    else if (command == "clear" && args.size() == 0)
    {
        dbManager.clear();
    }
    else if (command == "dump" && args.size() == 2)
    {
        dbManager.dump(args[0], args[1]);
    }
    else if (command == "load" && args.size() == 2)
    {
        dbManager.load(args[1], args[0]);
    }
    else if (command == "set")
    {
    }
    else
    {
        std::cout << "Invalid command or wrong number of arguments.\n";
        printUsage();
    }
}

nlohmann::json try_parse_json(const std::string &value)
{
    try
    {
        return nlohmann::json::parse(value);
    }
    catch (...)
    {
        return value;
    }
}