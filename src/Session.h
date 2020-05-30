#ifndef SESSION_H
#define SESSION_H

#include <optional>
#include "entities/User.h"
#include "controller/Controller.h"

class Session
{
private:
    std::optional<User> loggedUser;
    Controller controller;

public:
    Session();
    ~Session() = default;

    void start();
};
#endif
