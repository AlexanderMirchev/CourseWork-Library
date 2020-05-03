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
    UserRole userRole;
    std::optional<std::string> openedFile;
    std::unique_ptr<UserService> userService;
    std::unique_ptr<BookService> bookService;

public:
    Controller(std::unique_ptr<UserService> &&userService,
               std::unique_ptr<BookService> &&bookService)
        : userService{std::move(userService)},
          bookService{std::move(bookService)}, userRole{GUEST} {}

    bool hasLoggedUser() const;

    const std::unique_ptr<Result> runCommand(const std::vector<std::string> &);

private:
    static const size_t ONE_WORD = 1;
    static const size_t TWO_WORDS = 2;
    static const size_t THREE_WORDS = 3;
    static const size_t FOUR_WORDS = 4;

    static const std::string INVALID_COMMAND;

    static const std::string HELP_MESSAGE_GUEST;
    static const std::string HELP_MESSAGE_USER;
    static const std::string HELP_MESSAGE_ADMIN;

    // const std::function

    const std::unique_ptr<Result> validateAndExecute(
        const std::function<const std::unique_ptr<Result>()> &command,
        UserRole requiredRole, const size_t &requiredSize, const size_t &actualSize);

    const std::unique_ptr<Result> validateAndExecute(
        const std::function<const std::unique_ptr<Result>()> &command,
        UserRole requiredRole, const size_t &requiredSize, const size_t &actualSize) const;

    const std::unique_ptr<Result> open(const std::string &filename);
    const std::unique_ptr<Result> close();
    const std::unique_ptr<Result> save() const;
    const std::unique_ptr<Result> saveas(const std::string &filename);
    const std::unique_ptr<Result> help() const;
    const std::unique_ptr<Result> login(const std::string &username, const std::string &password);
    const std::unique_ptr<Result> logout();
    const std::unique_ptr<Result> booksAll() const;
    const std::unique_ptr<Result> booksInfo(const std::string &ISBN) const;
    const std::unique_ptr<Result> booksFind(const std::string &option,
                                            const std::string &optionString);
    const std::unique_ptr<Result> booksSort(const std::string &option, const std::string &order);
    const std::unique_ptr<Result> booksSort(const std::string &option);
    const std::unique_ptr<Result> usersAdd(const std::string &username, const std::string &password);
    const std::unique_ptr<Result> usersRemove(const std::string &username);

    using StringToBaseCommandMap = std::map<std::string, BaseCommand>;
    static const StringToBaseCommandMap COMMAND_MAP;

    static const BaseCommand findCommand(const std::string &command);
};
#endif
