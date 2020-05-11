#ifndef USER_H
#define USER_H

#include <string>
#include <vector>

#include "Serializable.h"

class User : public Serializable
{

private:
    std::string username;
    std::string password;
    bool admin;

public:
    /*
        See Serializable
    */
    const std::string objToString() const override;
    void stringToObject(const std::string &) override;

    /*
        Returns boolean value to determine whether user is admin or not.
    */
    bool isAdmin() const;

    /*
        Returns username string
    */
    const std::string &getUsername() const;

    /*
        Returns boolean value whether the password matches user password.
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
