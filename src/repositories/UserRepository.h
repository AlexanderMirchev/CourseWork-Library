#ifndef USERREPOSITORY_H
#define USERREPOSITORY_H

#include <optional>
#include <string>
#include <vector>

#include "../entities/User.h"

/*
    Interface for CRUD operations for users
*/
class UserRepository
{

public:
    virtual ~UserRepository() = default;

    /*
        Writes current list of users to file.
    */
    virtual void saveChanges() const = 0;

    /*
        Returns user with username.
        If no match is found nullopt is returned.
    */
    virtual const std::optional<User> getUserByUsername(
        const std::string &username) const = 0;

    /*
        Adds user to current list of users.
        If username already exists throws EntityAlreadyExistsException.
    */
    virtual void addUser(const User &) = 0;

    /*
        Removes user with username from current list of users.
        If no match is found throws EntityNotFoundException.
    */
    virtual void removeUserByUsername(const std::string &username) = 0;
};
#endif
