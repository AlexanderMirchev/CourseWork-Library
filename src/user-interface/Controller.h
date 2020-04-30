#ifndef _CONTROLLER_HH
#define _CONTROLLER_HH

#include <utility>
#include <string>
#include <optional>

#include "../Context.h"
#include "../entities/User.h"

using CommandPair = std::pair< std::string, std::optional<std::string> >;

class Controller
{
private:
    std::optional<User> user;
    Context context;

    enum BaseCommandList {
        InvalidCommand,
        OPEN,
        CLOSE,
        SAVE,
        SAVEAS,
        HELP,
        LOGIN,
        LOGOUT,
        EXIT,
        BOOKS,
        USERS
    };
public:
    Controller(const Context& context): user{std::nullopt} {
        this->context = context;
    }

    bool readCommand(const CommandPair&);

private:

    /*
        Parses command string to enum type
    */
    const BaseCommandList& resolveCommand(const std::string&) const;
    void setUser(const User&);
    void verify();
};

#endif