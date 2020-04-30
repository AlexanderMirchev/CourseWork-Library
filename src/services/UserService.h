#ifndef _USERSERVICE_HH
#define _USERSERVICE_HH

#include <optional>
#include <string>

#include "../entities/User.h"

// throws and optionals TODO
class UserService
{

public:
    virtual ~UserService() = default;

    /*
        Returns logged in user.
        optional/throws?
    */
    virtual const std::optional<User> &authenticateUser(
        const std::string &username, const std::string &password) const = 0;

    /*
        Creates non-admin user with username and password.
    */
    virtual void addUser(const std::string &username, const std::string &password) = 0;

    /*
        Removes user with username.
    */
    virtual void removeUser(const std::string &username) = 0;
};

#endif