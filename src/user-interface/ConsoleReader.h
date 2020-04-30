#ifndef _CONSOLEREADER_HH
#define _CONSOLEREADER_HH


class ConsoleReader {

public:
    ConsoleReader();
    void start();
    void readInput();
private:
    void processLine(const std::string&);
    /*
        Separates the line string into main command and leftover specification of command(could be empty).

        example: 
            books all -> pair ("books", "all")
            books title Introduction to programming -> pair ("books", "title Introduction to programming")
            exit -> pair("exit", std::nullopt)
    */
    std::pair< std::string, std::optional<std::string> > extractCommand(const std::string& line);
};

#endif