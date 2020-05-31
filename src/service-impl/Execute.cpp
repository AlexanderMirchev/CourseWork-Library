#ifndef EXECUTE_H
#define EXECUTE_H

#include <functional>

#include "../repositories/RepositoryExceptions.cpp"
#include "../services/ServiceExceptions.cpp"

/**
 * Methods catching all repository exceptions and 
 * transforming them to service exceptions whilst
 * invoking repository methods.
*/

/**
 * Tranforming into basic exceptions
*/
template <class Result>
Result execute(const std::function<Result()> &function)
{
    try
    {
        return function();
    }
    catch (SourceAlreadyExistsException &e)
    {
        throw AlreadyOpenException();
    }
    catch (NoSourceException &e)
    {
        throw NoOpenFileException();
    }
    catch (BadFormatException &e)
    {
        throw UnreadableFileException();
    }
}

/**
 * Transforming into more specific type exceptions
*/
template <class Result, class Function>
Result execute(const Function &function, const std::string &specifier)
{
    try
    {
        return function();
    }
    catch (SourceAlreadyExistsException &e)
    {
        throw AlreadyOpenException();
    }
    catch (NoSourceException &e)
    {
        throw NoOpenFileException();
    }
    catch (BadFormatException &e)
    {
        throw UnreadableFileException();
    }
    catch (EntityAlreadyExistsException &e)
    {
        throw AlreadyExistsException(specifier);
    }
    catch (EntityNotFoundException &e)
    {
        throw NotFoundException(specifier);
    }
}
#endif
