#include "Controller.h"

const std::unique_ptr<Result> Controller::runCommand(
    const std::vector<std::string> &extractedCommandIntoWords)
{
    if (extractedCommandIntoWords.empty())
    {
        return std::unique_ptr<Result>(new StringResult(INVALID_COMMAND));
    }

    const BaseCommand command = findCommand(extractedCommandIntoWords[0]);
    const size_t numberOfWords = extractedCommandIntoWords.size();

    switch (command)
    {
    case OPEN:
        return validateAndExecute(
            [this, extractedCommandIntoWords] {
                return open(extractedCommandIntoWords[1]);
            },
            GUEST, TWO_WORDS, numberOfWords);

    case CLOSE:
        return validateAndExecute(
            [this] {
                return close();
            },
            GUEST, ONE_WORD, numberOfWords);
    case SAVE:
        return validateAndExecute(
            [this] {
                return save();
            },
            GUEST, ONE_WORD, numberOfWords);
    case SAVEAS:
        return validateAndExecute(
            [this, extractedCommandIntoWords] {
                return saveas(extractedCommandIntoWords[1]);
            },
            GUEST, TWO_WORDS, numberOfWords);
    case HELP:
        return validateAndExecute(
            [this, extractedCommandIntoWords] {
                return help();
            },
            GUEST, ONE_WORD, numberOfWords);
    case LOGIN:
        return validateAndExecute(
            [this, extractedCommandIntoWords] {
                return login(extractedCommandIntoWords[1], extractedCommandIntoWords[2]);
            },
            GUEST, THREE_WORDS, numberOfWords);
    case LOGOUT:
        return validateAndExecute(
            [this] {
                return logout();
            },
            USER, ONE_WORD, numberOfWords);
    case BOOKS:
        if (numberOfWords > 1)
        {
            if (extractedCommandIntoWords[1] == "all")
            {
                return validateAndExecute(
                    [this] {
                        return booksAll();
                    },
                    USER, TWO_WORDS, numberOfWords);
            }
            if (extractedCommandIntoWords[1] == "find")
            {
                return validateAndExecute(
                    [this, extractedCommandIntoWords] {
                        return booksFind(extractedCommandIntoWords[2],
                                         extractedCommandIntoWords[3]);
                    },
                    USER, FOUR_WORDS, numberOfWords);
            }
            if (extractedCommandIntoWords[1] == "sort")
            {
                if (numberOfWords == 3)
                {
                    return validateAndExecute(
                        [this, extractedCommandIntoWords] {
                            return booksSort(extractedCommandIntoWords[2]);
                        },
                        USER, THREE_WORDS, numberOfWords);
                }
                return validateAndExecute(
                    [this, extractedCommandIntoWords] {
                        return booksSort(extractedCommandIntoWords[2],
                                         extractedCommandIntoWords[3]);
                    },
                    USER, FOUR_WORDS, numberOfWords);
            }
        }
        return std::unique_ptr<Result>(new StringResult(INVALID_COMMAND));
    case USERS:
        if (numberOfWords > 1)
        {
            if (extractedCommandIntoWords[1] == "add")
            {
                return validateAndExecute(
                    [this, extractedCommandIntoWords] {
                        return usersAdd(extractedCommandIntoWords[2],
                                        extractedCommandIntoWords[3]);
                    },
                    ADMIN, FOUR_WORDS, numberOfWords);
            }
            if (extractedCommandIntoWords[1] == "remove")
            {
                return validateAndExecute(
                    [this, extractedCommandIntoWords] {
                        return usersRemove(extractedCommandIntoWords[2]);
                    },
                    ADMIN, THREE_WORDS, numberOfWords);
            }
        }
        return std::unique_ptr<Result>(new StringResult(INVALID_COMMAND));
    default:
        return std::unique_ptr<Result>(new StringResult(INVALID_COMMAND));
    };
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
const Controller::BaseCommand Controller::findCommand(const std::string &command)
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
    std::string("books all - displays all books form file\n") + 
    std::string("books info <ISBN> - displays the book with the given isbn\n ") +
    std::string("books find <option> <option string>") + 
    std::string(" - finds all books by option(title, author, tag)\n ") + 
    std::string("books sort <option> [asc/desc] + - sorts all books by ") + 
    std::string("option(title,author, year, rating) in ascending descending order(optional)\n ");
const std::string Controller::HELP_MESSAGE_ADMIN = 
    HELP_MESSAGE_USER + 
    std::string("users add <username> <password> - creates new user with username and password\n ") +
    std::string("users remove <username> - removes user with username\n ");
