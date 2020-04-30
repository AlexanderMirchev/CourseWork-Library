#include "UserServiceImpl.h"

UserServiceImpl::UserServiceImpl(std::unique_ptr<UserRepository> &&userRepository)
    : userRepository{std::move(userRepository)} {}

const std::optional<User> &UserServiceImpl::authenticateUser(
    const std::string &username, const std::string &password) const
{

    std::optional<const User &> user = this->userRepository->getUserByUsername(username);
    if (user.has_value())
    {
        if (user.value().authenticate(password))
        {
            return user;
        }
    }
    return std::nullopt;
}
void UserServiceImpl::addUser(const std::string &username, const std::string &password)
{
    this->userRepository->addUser(User(username, password, false));
}
void UserServiceImpl::removeUser(const std::string &username)
{
    this->userRepository->removeUserByUsername(username);
}