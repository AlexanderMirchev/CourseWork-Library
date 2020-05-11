#include "Console.h"

const std::vector<std::string> Console::readInput(const std::string &line)
{
    std::vector<std::string> resCommandList;

    for (unsigned int i = 0; i < line.size(); i++)
    {
        if(line[i] == '"') {
            std::string tempString = extractWord(line, i, line[i]);
            if (!tempString.empty())
            {
                resCommandList.push_back(tempString);
            }
        }
        else if (line[i] != ' ')
        {
            std::string tempString = extractWord(line, i, ' ');
            if (!tempString.empty())
            {
                resCommandList.push_back(tempString);
            }
        }
    }
    return resCommandList;
}

void Console::display(const std::unique_ptr<Result> &result)
{
    result->display();
}

const std::string Console::extractWord(
    const std::string &line, unsigned int &posInLine, const char &delimeter)
{
    std::string word;
    bool haveNonDelimeters = false;
    while (posInLine < line.size())
    {
        if (line[posInLine] == delimeter)
        {
            if(haveNonDelimeters) return word;
        }
        else
        {
            if(line[posInLine] != ' ' || haveNonDelimeters) {
                word.push_back(line[posInLine]);
                haveNonDelimeters = true;
            }
        }
        ++posInLine;
    }

    if (delimeter == ' ')
    {
        return word;
    }
    else
    {
        return std::string();
    }
}
