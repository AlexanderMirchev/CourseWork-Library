#include "User.h"

User::User() : User(std::string(""), std::string(""), false) {}
User::User(const std::string &username, const std::string &password, const bool isAdmin)
{
    this->username = username;
    this->password = password;
    this->isAdmin = isAdmin;
}
User::User(User &&other)
{
    *this = other;
}
User &User::operator=(User &&other)
{
    this->username = std::move(other.username);
    this->password = std::move(other.password);
    this->isAdmin = other.isAdmin;
    return *this;
}
bool User::isAdmin() const
{
    return this->isAdmin;
}

const std::string &User::getUsername() const
{
    return this->username;
}
bool User::authenticate(const std::string &password) const
{
    return password == this->password;
}
const std::string User::objToString() const
{
    std::string result;

    result.append(username + ',');
    result.append(password + ',');
    result.append(isAdmin ? "T" : "F");

    return result;
}
void User::stringToObject(const std::string &string)
{
    std::vector<std::string> values = separateCSVs(string);

    int iterator = 0;
    this->username = values[iterator++];
    this->password = values[iterator++];
    if (values[iterator] == "T")
    {
        this->isAdmin = true;
    }
    else if (values[iterator] == "F")
    {
        this->isAdmin = false;
    }
}
