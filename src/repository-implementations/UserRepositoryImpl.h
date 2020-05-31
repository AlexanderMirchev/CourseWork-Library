#ifndef USERREPOSITORYIMPL_H
#define USERREPOSITORYIMPL_H

#include "EntitySerializer.h"

#include "../repositories/UserRepository.h"

/**
 * Implementation of UserRepository
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

    /**
     * May throw if sourcefile does not meet user requirements
    */
    UserRepositoryImpl(const std::string &sourceFile);
};
#endif
