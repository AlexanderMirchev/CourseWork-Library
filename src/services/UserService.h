#ifndef USERSERVICE_H
#define USERSERVICE_H

#include <optional>
#include <string>

#include "../entities/User.h"

/**
 * Service interface for actions with users
*/
class UserService
{

public:
    virtual ~UserService() = default;

    /**
     * Returns optional value for user if one with same username and password is found
    */
    virtual const std::optional<User> authenticateUser(
        const std::string &username, const std::string &password) const = 0;

    /**
     * Creates non-admin user with username and password.
     * 
     * Throws AlreadyExistsException
    */
    virtual void addUser(const std::string &username, const std::string &password) = 0;

    /**
     * Removes user with username.
     * 
     * Throws NotFoundException
    */
    virtual void removeUser(const std::string &username) = 0;
};
#endif
