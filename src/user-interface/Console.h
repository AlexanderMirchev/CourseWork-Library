#ifndef CONSOLE_H
#define CONSOLE_H

#include <string>
#include <vector>
#include <memory>

#include "ResultWrappers.cpp"

#include <utility>

#include "../entities/Book.h"
#include "../entities/User.h"
class Console
{
public:
    /*
        Separates a string into words and ignores trailing spaces
    */
    static const std::vector<std::string> readInput(const std::string &line);

    /*
        Overloaded function to display message onto console
    */
    static void display(const std::unique_ptr<Result> &result);

private:
    static const std::string extractWord(
        const std::string &line, unsigned int &posInLine, const char &delimeter);
};
#endif
