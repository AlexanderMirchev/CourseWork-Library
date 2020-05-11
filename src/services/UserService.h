#ifndef USERSERVICE_H
#define USERSERVICE_H

#include <optional>
#include <string>

#include "../entities/User.h"

/*
    Service interface for actions with users
*/
class UserService
{

public:
    virtual ~UserService() = default;

    /*
        Returns a user if one with same username and password is found
    */
    virtual const std::optional<User> authenticateUser(
        const std::string &username, const std::string &password) const = 0;

    /*
        Creates non-admin user with username and password.

        throws AlreadyExistsException when a user with same username is present
    */
    virtual void addUser(const std::string &username, const std::string &password) = 0;

    /*
        Removes user with username.

        throws NotFoundException when user can't be found to be deleted
    */
    virtual void removeUser(const std::string &username) = 0;
};
#endif
