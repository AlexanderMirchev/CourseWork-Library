#include "Controller.h"

std::unique_ptr<Result> Controller::open(const std::string &filename)
{
    this->bookService->openFile(filename);
    return std::unique_ptr<Result>(new StringResult("File successfully opened."));
}
std::unique_ptr<Result> Controller::close()
{
    this->bookService->closeFile();
    return std::unique_ptr<Result>(new StringResult("File successfully closed."));
}
std::unique_ptr<Result> Controller::save() const
{
    this->bookService->saveFile();
    return std::unique_ptr<Result>(new StringResult("File successfully saved."));
}
std::unique_ptr<Result> Controller::saveas(const std::string &filename)
{
    this->bookService->saveFileAs(filename);
    return std::unique_ptr<Result>(
        new StringResult("File successfully saved in new file."));
}
std::unique_ptr<Result> Controller::help(const UserRole &role) const
{
    std::string message;
    switch (role)
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
std::unique_ptr<Result> Controller::login(
    const std::string &username, const std::string &password) const
{
    const std::optional<User> user = this->userService->authenticateUser(username, password);
    if (user.has_value())
    {
        return std::unique_ptr<Result>(new UserLoginResult(user.value()));
    }
    return std::unique_ptr<Result>(new StringResult("No such user found."));
}
