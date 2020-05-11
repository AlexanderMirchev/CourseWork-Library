#include "UserRepositoryImpl.h"

#include "../repositories/RepositoryExceptions.cpp"

UserRepositoryImpl::UserRepositoryImpl(const std::string &sourceFile) : serializer{EntitySerializer<User>(sourceFile)}
{
    this->users = this->serializer.readAllEntities();
}

void UserRepositoryImpl::saveChanges() const
{
    this->serializer.writeAllEntities(this->users);
}

const std::optional<User> UserRepositoryImpl::getUserByUsername(
    const std::string &username) const
{
    for (const User &user : this->users)
    {
        if (user.getUsername() == username)
        {
            return user;
        }
    }
    return std::nullopt;
}
void UserRepositoryImpl::addUser(const User &user)
{
    if (getUserByUsername(user.getUsername()).has_value())
    {
        throw EntityAlreadyExistsException();
    }
    else
    {
        this->users.push_back(user);
    }
    saveChanges();
}
void UserRepositoryImpl::removeUserByUsername(const std::string &username)
{
    std::vector<User> newUsers;
    bool userWithUsernameExists = false;
    for (const User &user : this->users)
    {
        if (user.getUsername() == username)
        {
            userWithUsernameExists = true;
        }
        else
        {
            newUsers.push_back(user);
        }
    }

    if (!userWithUsernameExists)
    {
        throw EntityNotFoundException();
    }
    else
    {
        this->users = newUsers;
    }
    saveChanges();
}