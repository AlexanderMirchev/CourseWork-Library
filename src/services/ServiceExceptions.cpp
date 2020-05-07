#include <exception>
#include <string>

/*
    Base service exception
*/
struct ServiceException : public std::exception
{
    virtual ~ServiceException() = default;

    virtual const char *what() const throw() = 0;
};

/*
    NoOpenFileException for when the user has no open file
*/
struct NoOpenFileException : public ServiceException
{
    const char *what() const throw() override
    {
        return "There is no open file.";
    }
};

struct AlreadyOpenException : public ServiceException
{
    const char *what() const throw() override
    {
        return "There is already an open file.";
    }
};

struct UnreadableFileException : public ServiceException
{

    const char *what() const throw() override
    {
        return "The given file can't be read.";
    }
};

class AlreadyExistsException : public ServiceException
{
private:
    std::string type;

public:
    AlreadyExistsException() = delete;
    AlreadyExistsException(const std::string &type) : type{type} {}
    const char *what() const throw() override
    {
        return (std::string(type) + " already exists.").c_str();
    }
};

class NotFoundException : public ServiceException
{
private:
    std::string type;

public:
    NotFoundException() = delete;
    NotFoundException(const std::string &type) : type{type} {}
    const char *what() const throw() override
    {
        return (std::string(type) + " not found.").c_str();
    }
};

class InvalidParamException : public ServiceException
{
private:
    std::string type;

public:
    InvalidParamException() = delete;
    InvalidParamException(const std::string &type) : type{type} {}
    const char *what() const throw() override
    {
        return (std::string(type) + " is invalid.").c_str();
    }
};
