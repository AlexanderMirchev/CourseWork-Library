#include <iostream>
#include <optional>
#include <string>
#include <utility>
#include "../entities/User.h"
#include "ConsoleReader.h"


ConsoleReader::ConsoleReader() { }

void ConsoleReader::start() {
    // TODO GREETING TEXT
    while (true) {
        std::string line;
        std::getline(std::cin, line);

        std::pair< std::string, std::optional<std::string> > baseAndSpecificationOfCommand = 
            extractCommand(line);
    }
    
}

void ConsoleReader::readInput() {
    std::string line;
    while (true) {
        getline(std::cin, line);
        if(line.compare("exit")) {
            return;
        }

        processLine(line);
    }
}
std::pair< std::string, std::optional<std::string> > ConsoleReader::extractCommand(const std::string& line) {
    size_t indexOfFirstNonSpace = line.find_first_not_of(" ");
    if(indexOfFirstNonSpace == std::string::npos) {
        return std::pair< std::string, std::optional<std::string> >(std::string(""), std::nullopt);
    }

    // extract the first word from input 
    size_t indexOfFirstSpaceAfterCharacter = line.find_first_of(" ", indexOfFirstNonSpace);
    std::string command = line.substr(indexOfFirstNonSpace, 
        indexOfFirstSpaceAfterCharacter - indexOfFirstNonSpace);
    
    // extracts the remainder of spaces removing trailing spaces
    std::optional<std::string> additional;
    if(indexOfFirstSpaceAfterCharacter != std::string::npos) {
        size_t firstCharIndexOfNextWord = line.find_first_not_of(" ", indexOfFirstSpaceAfterCharacter + 1);
        if(firstCharIndexOfNextWord != std::string::npos) {
            size_t lastNonSpaceCharacter = line.find_last_not_of(" ");
            return std::pair< std::string, std::optional<std::string> >(command, 
                line.substr(firstCharIndexOfNextWord, lastNonSpaceCharacter));
        }        
    } 

    return std::pair< std::string, std::optional<std::string> > (command, std::nullopt);
}
