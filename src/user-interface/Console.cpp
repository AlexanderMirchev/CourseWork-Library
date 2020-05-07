#include "Console.h"

const std::vector<std::string> Console::readInput(const std::string &line)
{
    std::vector<std::string> resCommandList;

    std::string tempString;
    for (size_t i = 0; i < line.size(); i++)
    {
        if (line[i] != ' ')
        {
            tempString.push_back(line[i]);
        }
        else
        {
            if (!tempString.empty())
            {
                resCommandList.push_back(tempString);
                tempString.clear();
            }
        }
    }
    if (!tempString.empty())
    {
        resCommandList.push_back(tempString);
    }
    return resCommandList;
}

void Console::display(const std::unique_ptr<Result> &result)
{
    result->display();
}