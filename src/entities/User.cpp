#include "User.h"
#include "../repositories/RepositoryExceptions.cpp"

User::User() : User(std::string(""), std::string(""), false) {}
User::User(const std::string &username, const std::string &password, const bool admin)
{
    this->username = username;
    this->password = password;
    this->admin = admin;
}
User::User(User &&other)
{
    *this = other;
}
User &User::operator=(User &&other)
{
    this->username = std::move(other.username);
    this->password = std::move(other.password);
    this->admin = other.admin;
    return *this;
}
bool User::isAdmin() const
{
    return this->admin;
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
    result.append(admin ? "T" : "F");

    return result;
}
void User::stringToObject(const std::string &string)
{
    std::vector<std::string> values = separateCSVs(string);
    const size_t exactRequiredSize = 3;
    if (values.size() != exactRequiredSize)
    {
        throw BadFormatException();
    }
    

    int iterator = 0;
    this->username = values[iterator++];
    this->password = values[iterator++];
    if (values[iterator] == "T")
    {
        this->admin = true;
    }
    else if (values[iterator] == "F")
    {
        this->admin = false;
    }
}
