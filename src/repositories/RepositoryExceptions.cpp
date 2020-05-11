#ifndef REPOSITORYEXCEPTIONS_H
#define REPOSITORYEXCEPTIONS_H

#include <exception>

/*
    Base repository exception
*/
struct RepositoryException : public std::exception
{
    virtual ~RepositoryException() = default;

    virtual const char *what() const throw() = 0;
};

/*
    Exception for when a new source is trying to 
    be opened while there is already an open one.
*/
struct SourceAlreadyExistsException : public RepositoryException
{
    const char *what() const throw() override
    {
        return "There is an existing source already. \n";
    }
};

/*
    Exception for when a method requiring a source is 
    invoked while no current source exists.
*/
struct NoSourceException : public RepositoryException
{
    const char *what() const throw() override
    {
        return "No source could be found. \n";
    }
};

/*
    Exception for when an error occurs while reading file.
*/
struct BadFormatException : public RepositoryException
{
    const char *what() const throw() override
    {
        return "Invalid format. \n";
    }
};

/*
    Exception for when an entity is to be added to current 
    list of entities, but does not satisfy an unique constraint.
    (one of the fields should be unique)
*/
struct EntityAlreadyExistsException : public RepositoryException
{
    const char *what() const throw() override
    {
        return "Entity already exists. \n";
    }
};

/*
    Exception for when a change is to be made to a certain entity 
    but no entites match the given search criteria.
*/
struct EntityNotFoundException : public RepositoryException
{
    const char *what() const throw() override
    {
        return "No such entity found. \n";
    }
};
#endif
