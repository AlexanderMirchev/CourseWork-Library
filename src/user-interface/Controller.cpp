#include "Controller.h"
Controller::Controller(std::unique_ptr<UserService> &&userService,
                       std::unique_ptr<BookService> &&bookService)
    : userService{std::move(userService)},
      bookService{std::move(bookService)}, userRole(GUEST) {}
const std::unique_ptr<Result> Controller::runCommand(
    const std::vector<std::string> &commands)
{
    if (commands.empty())
    {
        return std::unique_ptr<Result>(new StringResult(INVALID_COMMAND));
    }

    const BaseCommand command = findCommand(commands[0]);

    switch (command)
    {
    case OPEN:
        return validateAndExecute(
            [this, commands] {
                return open(commands[1]);
            },
            GUEST, Controller::TWO_WORDS, commands.size());

    case CLOSE:
        return validateAndExecute(
            [this] {
                return close();
            },
            GUEST, Controller::ONE_WORD, commands.size());
    case SAVE:
        return validateAndExecute(
            [this] {
                return save();
            },
            GUEST, Controller::ONE_WORD, commands.size());
    case SAVEAS:
        return validateAndExecute(
            [this, commands] {
                return saveas(commands[1]);
            },
            GUEST, Controller::TWO_WORDS, commands.size());
    case HELP:
        return validateAndExecute(
            [this, commands] {
                return help();
            },
            GUEST, Controller::ONE_WORD, commands.size());
    case LOGIN:
        return validateAndExecute(
            [this, commands] {
                return login(commands[1], commands[2]);
            },
            GUEST, Controller::THREE_WORDS, commands.size());
    case LOGOUT:
        return validateAndExecute(
            [this] {
                return logout();
            },
            USER, Controller::ONE_WORD, commands.size());
    case BOOKS:
        if (commands.size() > 1)
        {
            return books(commands);
        }
        return std::unique_ptr<Result>(new StringResult(INVALID_COMMAND));
    case USERS:
        if (commands.size() > 1)
        {
            return users(commands);
        }
        return std::unique_ptr<Result>(new StringResult(INVALID_COMMAND));
    default:
        return std::unique_ptr<Result>(new StringResult(INVALID_COMMAND));
    };
}
bool Controller::hasLoggedUser() const {
    return loggedUser.has_value();
}
const Controller::StringToBaseCommandMap Controller::COMMAND_MAP = {
    {"open", OPEN},
    {"close", CLOSE},
    {"save", SAVE},
    {"saveas", SAVEAS},
    {"help", HELP},
    {"login", LOGIN},
    {"logout", LOGOUT},
    {"books", BOOKS},
    {"users", USERS}};
Controller::BaseCommand Controller::findCommand(const std::string &command)
{
    StringToBaseCommandMap::const_iterator mapEntry = COMMAND_MAP.find(command);
    if (mapEntry == COMMAND_MAP.end())
    {
        return InvalidCommand;
    }
    return mapEntry->second;
}
const std::unique_ptr<Result> Controller::validateAndExecute(
    const std::function<const std::unique_ptr<Result>()> &command,
    UserRole requiredRole, const size_t &requiredSize, const size_t &actualSize)
{
    // effective c++ solution to methods with same code but different qualifiers
    return std::as_const(*this)
        .validateAndExecute(command, requiredRole, requiredSize, actualSize);
}
const std::unique_ptr<Result> Controller::validateAndExecute(
    const std::function<const std::unique_ptr<Result>()> &command,
    UserRole requiredRole, const size_t &requiredSize, const size_t &actualSize) const
{
    if (requiredRole > this->userRole)
    {
        return std::unique_ptr<Result>(
            new StringResult("You are not authorized to perform this action."));
    }
    if (requiredSize != actualSize)
    {
        return std::unique_ptr<Result>(
            new StringResult("The amount of parameters does not match any function."));
    }
    try
    {
        return command();
    }
    catch (const ServiceException &e)
    {
        return std::unique_ptr<Result>(new StringResult(e.what()));
    }
    catch (const std::exception &e)
    {
        return std::unique_ptr<Result>(new StringResult("Unknown error."));
    }
}
const std::string Controller::INVALID_COMMAND = "No recognized command";

const std::string Controller::HELP_MESSAGE_GUEST =
    std::string("Help:\n open <filename> - opens file to read from\n ") +
    std::string("close - closes opened file\n save - saves current changes to file\n ") +
    std::string("saveas <filename> - saves current changes to given file\n ") +
    std::string("exit - exits the program\n login - login for user with username and password\n ");
const std::string Controller::HELP_MESSAGE_USER =
    HELP_MESSAGE_GUEST + std::string("logout - logouts the current user\n ") +
    std::string("books all - displays all books form file\n ") +
    std::string("books info <ISBN> - displays the book with the given isbn\n ") +
    std::string("books find <option> <option string>") +
    std::string(" - finds all books by option(title, author, tag)\n ") +
    std::string("books sort <option> [asc/desc] + - sorts all books by ") +
    std::string("option(title,author, year, rating) in ascending or descending order(optional)\n ");
const std::string Controller::HELP_MESSAGE_ADMIN =
    HELP_MESSAGE_USER +
    std::string("users add <username> <password> - creates new user with username and password\n ") +
    std::string("users remove <username> - removes user with username\n ");

const size_t Controller::ONE_WORD = 1;
const size_t Controller::TWO_WORDS = 2;
const size_t Controller::THREE_WORDS = 3;
const size_t Controller::FOUR_WORDS = 4;
