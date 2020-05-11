#ifndef _CONTROLLER_H
#define _CONTROLLER_H

#include <memory>
#include <utility>
#include <map>
#include <string>
#include <optional>
#include <utility>

#include "../entities/User.h"
#include "../services/UserService.h"
#include "../services/BookService.h"
#include "../services/ServiceExceptions.cpp"
#include "ResultWrappers.cpp"

/*
    A class that resolves the command provided by user and redirects it accordingly
*/
class Controller
{
private:
    enum UserRole
    {
        GUEST,
        USER,
        ADMIN
    };
    enum BaseCommand
    {
        InvalidCommand,
        OPEN,
        CLOSE,
        SAVE,
        SAVEAS,
        HELP,
        LOGIN,
        LOGOUT,
        BOOKS,
        USERS
    };

    std::optional<User> loggedUser;
    std::optional<std::string> openedFile;
    std::unique_ptr<UserService> userService;
    std::unique_ptr<BookService> bookService;
    UserRole userRole;

public:
    Controller(std::unique_ptr<UserService> &&userService,
               std::unique_ptr<BookService> &&bookService);

    /*
        A check whether the current session has user
    */
    bool hasLoggedUser() const;

    /*
        Redirects which function to be called according to the list of commands
    */
    const std::unique_ptr<Result> runCommand(const std::vector<std::string> &);

private:
    static const size_t ONE_WORD;
    static const size_t TWO_WORDS;
    static const size_t THREE_WORDS;
    static const size_t FOUR_WORDS;

    static const std::string INVALID_COMMAND;

    static const std::string HELP_MESSAGE_GUEST;
    static const std::string HELP_MESSAGE_USER;
    static const std::string HELP_MESSAGE_ADMIN;

    /*
        Functions to absorb the lower-level exceptions into user output
    */
    const std::unique_ptr<Result> validateAndExecute(
        const std::function<const std::unique_ptr<Result>()> &command,
        UserRole requiredRole, const size_t &requiredSize, const size_t &actualSize);

    const std::unique_ptr<Result> validateAndExecute(
        const std::function<const std::unique_ptr<Result>()> &command,
        UserRole requiredRole, const size_t &requiredSize, const size_t &actualSize) const;

    /*
        Generic commands
    */
    const std::unique_ptr<Result> open(const std::string &filename);
    const std::unique_ptr<Result> close();
    const std::unique_ptr<Result> save() const;
    const std::unique_ptr<Result> saveas(const std::string &filename);
    const std::unique_ptr<Result> help() const;
    const std::unique_ptr<Result> login(const std::string &username, const std::string &password);
    const std::unique_ptr<Result> logout();

    /*
        Book commands
    */
    const std::unique_ptr<Result> books(const std::vector<std::string> &commands);
    const std::unique_ptr<Result> booksAll() const;
    const std::unique_ptr<Result> booksInfo(const std::string &ISBN) const;
    const std::unique_ptr<Result> booksFind(const std::string &option,
                                            const std::string &optionString);
    const std::unique_ptr<Result> booksSort(const std::string &option, const std::string &order);
    const std::unique_ptr<Result> booksSort(const std::string &option);

    /*
        User commands
    */
    const std::unique_ptr<Result> users(const std::vector<std::string> &commands);
    const std::unique_ptr<Result> usersAdd(const std::string &username, const std::string &password);
    const std::unique_ptr<Result> usersRemove(const std::string &username);

    /*
        Map containing pairs of string and enum BaseCommand
    */
    using StringToBaseCommandMap = std::map<std::string, BaseCommand>;
    static const StringToBaseCommandMap COMMAND_MAP;
    static BaseCommand findCommand(const std::string &command);
};
#endif
