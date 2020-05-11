#include "Controller.h"
#include <cassert>

const std::unique_ptr<Result> Controller::users(const std::vector<std::string> &commands)
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
            ADMIN, FOUR_WORDS, numberOfWords);
    }
    if (commands[1] == "remove")
    {
        return validateAndExecute(
            [this, commands] {
                return usersRemove(commands[2]);
            },
            ADMIN, THREE_WORDS, numberOfWords);
    }
}
const std::unique_ptr<Result> Controller::usersAdd(
    const std::string &username, const std::string &password)
{
    this->userService->addUser(username, password);
    return std::unique_ptr<Result>(new StringResult("User successfully added."));
}
const std::unique_ptr<Result> Controller::usersRemove(const std::string &username)
{
    this->userService->removeUser(username);
    return std::unique_ptr<Result>(new StringResult("User successfully removed."));
}
