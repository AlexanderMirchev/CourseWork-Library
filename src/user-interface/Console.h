#ifndef CONSOLE_H
#define CONSOLE_H

#include <string>
#include <vector>
#include <memory>

#include "../controller/ResultWrappers.h"

#include <utility>

#include "../entities/Book.h"
#include "../entities/User.h"

/**
 * Class for interraction with console
*/
class Console
{
public:
    /**
     * Separates line string into separate words with specific rules:
     * if ' " ' is present, a new word will be added only after a second one is seen
     * else on every space a new word is added to list
     * 
     * Example:
     * books find author "Ivan Vazov" - 4 words
     * books find author Ivan Vazov - 5 words
    */
    static const std::vector<std::string> readInput(const std::string &line);

    /**
     * Displays the value of the result
    */
    static void display(const std::unique_ptr<Result> &result);

private:
    static const std::string extractWord(
        const std::string &line, unsigned int &posInLine, const char &delimeter);
};
#endif
