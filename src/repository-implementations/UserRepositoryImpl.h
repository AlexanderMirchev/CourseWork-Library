#ifndef USERREPOSITORYIMPL_H
#define USERREPOSITORYIMPL_H

#include "EntitySerializer.h"

#include "../repositories/UserRepository.h"

/*
    Implementation of UserRepository
*/
class UserRepositoryImpl : public UserRepository
{

private:
    EntitySerializer<User> serializer;
    std::vector<User> users;

public:
    void saveChanges() const override;
    const std::optional<User> getUserByUsername(
        const std::string &username) const override;
    void addUser(const User &user) override;
    void removeUserByUsername(const std::string &username) override;

    /*
        Creates repository object with and sets the source file name to sourseFile.
        Gets all users in file.

        Throws BadFormatException (mostly should be preset so it does not throw)
    */
    UserRepositoryImpl(const std::string &sourceFile);
};
#endif
