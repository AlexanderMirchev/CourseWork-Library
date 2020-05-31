#ifndef SESSION_H
#define SESSION_H

#include <optional>
#include "entities/User.h"
#include "controller/Controller.h"

/**
 * Class for encapsulation of user data and actions
*/
class Session
{
private:
    std::optional<User> loggedUser;
    Controller controller;

public:
    Session();
    ~Session() = default;

    /**
     * Starts input of data
    */
    void start();
};
#endif
