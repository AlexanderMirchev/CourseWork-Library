#ifndef _USERREPOSITORYIMPL_HH
#define _USERREPOSITORYIMPL_HH

#include "EntitySerializer.h"

#include "../repositories/UserRepository.h"

class UserRepositoryImpl : public UserRepository
{

private:
    EntitySerializer<User> serializer;
    std::vector<User> users;

public:
    void saveChanges() const override;

    const const std::optional<const User &> &getUserByUsername(
        const std::string &username) const override;

    void addUser(const User &user) override;

    void removeUserByUsername(const std::string &username) override;

    UserRepositoryImpl(const std::string &sourceFile);
};
#endif
