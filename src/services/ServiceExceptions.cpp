#include <exception>
#include <string>

/*
    Service level exceptions to be thrown by the service layer and
    provided to user.
*/

/*
    Base service exception
*/
struct ServiceException : public std::exception
{
    virtual ~ServiceException() = default;

    virtual const char *what() const throw() = 0;
};

/*
    NoOpenFileException for when the user tries to complete operation
    requiring an open file but none is current
*/
struct NoOpenFileException : public ServiceException
{
    const char *what() const throw() override
    {
        return "There is no open file.";
    }
};

/*
    AlreadyOpenException for when the user tries to open a file while
    there is already one open
*/
struct AlreadyOpenException : public ServiceException
{
    const char *what() const throw() override
    {
        return "There is already an open file.";
    }
};

/*
    UnreadableFileException for when the user requests read operation
    from a file and the system is unable to complete it
*/
struct UnreadableFileException : public ServiceException
{

    const char *what() const noexcept override
    {
        return "The given file can't be read.";
    }
};

/*
    AlreadyExistsException for when the user tries to create an object
    but it does not comply with an unique constraint.
    Has type identifier.
*/
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
    const char *what() const noexcept override
    {
        return message.c_str();
    }
};

/*
    NotFoundException for when a non-read operation is requested for a single
    entity.
    Has type identifier.
*/
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
    const char *what() const noexcept override
    {
        return message.c_str();
    }
};

/*
    InvalidParamException for when an identifier is passed through
    the command parameters and it does not match the function's
    specification.
    Has type identifier.
*/
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
    const char *what() const noexcept override
    {
        return message.c_str();
    }
};
