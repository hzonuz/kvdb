#include "main.h"
#include "db.h"
#include "utils.h"

int main()
{
    DatabaseManager dbManager;

    std::string line, command;
    std::string token;

    printUsage();
    while (true)
    {
        try
        {
            std::cout << "# ";
            std::getline(std::cin, line);
            std::stringstream ss(line);
            std::vector<std::string> args;

            while (ss >> token)
            {
                if (command.empty())
                {
                    command = token;
                }
                else if (command == "set")
                {
                    std::string key, value;
                    key = token;
                    if (std::getline(ss >> std::ws, value))
                    {
                        dbManager.set(key, value);
                        break;
                    }
                }
                else
                {
                    args.push_back(token);
                }
            }

            if (command == "exit")
            {
                break;
            }

            std::cout << "> ";

            executeCommand(dbManager, command, args);

            std::cout << std::endl;

            command.clear();
        }
        catch (const std::exception &e)
        {
            std::cerr << e.what() << '\n';
        }
    }

    return 0;
}