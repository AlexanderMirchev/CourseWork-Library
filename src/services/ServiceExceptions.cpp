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
    std::string message;

public:
    AlreadyExistsException() = delete;
    AlreadyExistsException(const std::string &type)
    {
        message = type;
        message += " already exists.";
    }
    const char *what() const throw() override
    {
        return message.c_str();
    }
};

class NotFoundException : public ServiceException
{
private:
    std::string message;

public:
    NotFoundException() = delete;
    NotFoundException(const std::string &type)
    {
        message = type;
        message += " not found.";
    }
    const char *what() const throw() override
    {
        return message.c_str();
    }
};

class InvalidParamException : public ServiceException
{
private:
    std::string message;

public:
    InvalidParamException() = delete;
    InvalidParamException(const std::string &type)
    {
        message = type;
        message += " is invalid.";
    }
    const char *what() const throw() override
    {
        return message.c_str();
    }
};
