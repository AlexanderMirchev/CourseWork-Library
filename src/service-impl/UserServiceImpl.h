#ifndef USERSERVICEIMPL_H
#define USERSERVICEIMPL_H

#include <memory>

#include "../services/UserService.h"
#include "../repositories/UserRepository.h"

class UserServiceImpl : public UserService
{

private:
    std::unique_ptr<UserRepository> userRepository;

public:
    const std::optional<User> &authenticateUser(
        const std::string &username, const std::string &password) const override;

    void addUser(const std::string &username, const std::string &password) override;

    void removeUser(const std::string &username) override;

    UserServiceImpl(std::unique_ptr<UserRepository> &&userRepository);
};
#endif
