#ifndef _CONSOLE_HH
#define _CONSOLE_HH

#include <string>
#include <vector>

#include <utility>

#include"../entities/Book.h"
#include"../entities/User.h"
class Console
{
private:
    /* data */
public:
    Console(/* args */);
    ~Console();

    void start();
    const std::vector<std::string> readInput();

    void display(std::vector<Book>);
};
#endif
