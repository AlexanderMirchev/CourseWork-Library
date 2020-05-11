#include "Controller.h"

const std::unique_ptr<Result> Controller::open(const std::string &filename)
{
    this->bookService->openFile(filename);
    this->openedFile = filename;
    return std::unique_ptr<Result>(new StringResult("File successfully opened."));
}
const std::unique_ptr<Result> Controller::close()
{
    this->bookService->closeFile();
    this->openedFile = std::nullopt;
    return std::unique_ptr<Result>(new StringResult("File successfully closed."));
}
const std::unique_ptr<Result> Controller::save() const
{
    this->bookService->saveFile();
    return std::unique_ptr<Result>(new StringResult("File successfully saved."));
}
const std::unique_ptr<Result> Controller::saveas(const std::string &filename)
{
    this->bookService->saveFileAs(filename);
    return std::unique_ptr<Result>(
        new StringResult("File successfully saved in new file."));
}
const std::unique_ptr<Result> Controller::help() const
{
    std::string message;
    switch (this->userRole)
    {
    case GUEST:
        message = HELP_MESSAGE_GUEST;
        break;
    case USER:
        message = HELP_MESSAGE_USER;
        break;
    case ADMIN:
        message = HELP_MESSAGE_ADMIN;
        break;
    default:
        break;
    }
    return std::unique_ptr<Result>(new StringResult(message));
}
const std::unique_ptr<Result> Controller::login(
    const std::string &username, const std::string &password)
{
    const std::optional<User> user = this->userService->authenticateUser(username, password);
    if (user.has_value())
    {
        this->loggedUser = user;
        this->userRole = this->loggedUser.value().isAdmin() ? ADMIN : USER;

        return std::unique_ptr<Result>(new StringResult("Successfully logged in."));
    }
    return std::unique_ptr<Result>(new StringResult("No such user found."));
}
const std::unique_ptr<Result> Controller::logout()
{
    if (loggedUser.has_value())
    {
        this->loggedUser = std::nullopt;
        this->userRole = GUEST;
        return std::unique_ptr<Result>(new StringResult("Successfully logged out."));
    }
    return std::unique_ptr<Result>(
        new StringResult("You can't log out if you are not logged in."));
}
