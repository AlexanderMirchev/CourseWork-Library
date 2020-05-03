#include "Console.h"

const std::vector<std::string> readInput(const std::string &line)
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
    return resCommandList;
}

void display(std::vector<Book>);