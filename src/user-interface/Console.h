#ifndef _CONSOLE_HH
#define _CONSOLE_HH

#include <string>
#include <vector>

#include <utility>

#include "../entities/Book.h"
#include "../entities/User.h"
class Console
{
public:
    /*
        Separates a string into words and ignores trailing spaces
    */
    const std::vector<std::string> readInput(const std::string &line);

    /*
        Overloaded function to display message onto console
    */
    void display(const std::string& caseTitle, const std::vector<Book>& result);

    void display(const std::string& caseTitle, const Book& result);

    void display(const std::string& caseTitle, const std::string& result);
};
#endif
