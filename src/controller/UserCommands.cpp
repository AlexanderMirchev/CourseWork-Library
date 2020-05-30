#include "Controller.h"
#include <cassert>

std::unique_ptr<Result> Controller::users(
    const std::vector<std::string> &commands, const UserRole &role)
{
    const unsigned int numberOfWords = commands.size();
    assert(numberOfWords > 1);
    if (commands[1] == "add")
    {
        return validateAndExecute(
            [this, commands] {
                return usersAdd(commands[2],
                                commands[3]);
            },
            ADMIN, role, FOUR_WORDS, numberOfWords);
    }
    if (commands[1] == "remove")
    {
        return validateAndExecute(
            [this, commands] {
                return usersRemove(commands[2]);
            },
            ADMIN, role, THREE_WORDS, numberOfWords);
    }
    return std::unique_ptr<Result>(new StringResult(INVALID_COMMAND));
}
std::unique_ptr<Result> Controller::usersAdd(
    const std::string &username, const std::string &password)
{
    this->userService->addUser(username, password);
    return std::unique_ptr<Result>(new StringResult("User successfully added."));
}
std::unique_ptr<Result> Controller::usersRemove(const std::string &username)
{
    this->userService->removeUser(username);
    return std::unique_ptr<Result>(new StringResult("User successfully removed."));
}
