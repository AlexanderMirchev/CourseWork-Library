#include <exception>

/*
    Base service exception
*/
struct ServiceException : public std::exception
{
    virtual ~ServiceException();

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



