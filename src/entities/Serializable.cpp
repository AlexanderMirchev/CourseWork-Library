#include "Serializable.h"

const std::vector<std::string> Serializable::separateCSVs(const std::string &string)
{
    std::vector<std::string> resList;
    std::string tempStr;

    map(string, [&](const char &character) -> void {
        if (character == ',')
        {
            resList.push_back(tempStr);
            tempStr.clear();
        }
        else
        {
            tempStr.push_back(character);
        }
    });
    resList.push_back(tempStr);

    return resList;
}

void Serializable::map(const std::string &string, const std::function<void(const char &)> &func)
{
    for (size_t i = 0; i < string.size(); i++)
    {
        func(string[i]);
    }
}