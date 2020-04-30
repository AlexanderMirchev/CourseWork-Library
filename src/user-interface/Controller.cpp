#include "Controller.h"

bool Controller::readCommand(
    const CommandPair& commandPair) {
        switch (resolveCommand(commandPair.first)) {
        case OPEN:
            if(!commandPair.second.has_value) {
                // throw
            }
            // try
            this->context.open(commandPair.second.value);
            break;
        case CLOSE:
            if(commandPair.second.has_value) {
                // throw
            }
            // try
            this->context.close();
            break;
        case SAVE:
            if(commandPair.second.has_value) {
                // throw
            }
            // try
            this->context.save();
            break;
        case SAVEAS:
            if(!commandPair.second.has_value) {
                this->context.save();
            }
            this->context.saveas(commandPair.second.value);
            break;
        case LOGIN:
            if(commandPair.second.has_value) {
                // throw
            }
            // std::cin
            
            break;
        case LOGOUT:
            if(commandPair.second.has_value) {
                // throw
            }

            if(!this->user.has_value) {
                // throw
            }
            else {
                this->user = std::nullopt;
            }
            
            break;
        case HELP:
            if(commandPair.second.has_value) {
                // throw
            }
            // std::cin
            
            break;
        case BOOKS:
            if(commandPair.second.has_value) {
                // throw
            }
            // std::cin
            
            break;
        
        default:
            break;
        }
}
const Controller::BaseCommandList& Controller::resolveCommand(
    const std::string& commandString) const {
        if(commandString == "open") {
            return Controller::OPEN;
        } else if (commandString == "close") {
            return Controller::CLOSE;
        } else if (commandString == "save") {
            return Controller::SAVE;
        } else if (commandString == "saveas") {
            return Controller::SAVEAS;
        } else if (commandString == "help") {
            return Controller::HELP;
        } else if (commandString == "login") {
            return Controller::LOGIN;
        } else if (commandString == "logout") {
            return Controller::LOGOUT;
        } else if (commandString == "exit") {
            return Controller::EXIT;
        } else if (commandString == "books") {
            return Controller::BOOKS;
        } else if (commandString == "users") {
            return Controller::USERS;
        } else {
            return Controller::InvalidCommand;
        }
}

void Controller::setUser(const User& user) {
    this->user = user;
}

