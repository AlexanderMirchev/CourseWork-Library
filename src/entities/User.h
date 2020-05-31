#ifndef USER_H
#define USER_H

#include <string>
#include <vector>

#include "Serializable.h"

/**
 * An entity class for a user
*/
class User : public Serializable
{

private:
    std::string username;
    std::string password;
    bool admin;

public:
    const std::string objToString() const override;
    void stringToObject(const std::string &) override;

    /**
     * Boolean value if user has admin rights
    */
    bool isAdmin() const;

    const std::string &getUsername() const;

    /**
     * Boolean value whether param password is the same as user password
    */
    bool authenticate(const std::string &password) const;

    User();
    User(const std::string &, const std::string &, const bool);
    User(const User &) = default;
    ~User() = default;
    User &operator=(const User &) = default;
    User(User &&);
    User &operator=(User &&);
};
#endif
