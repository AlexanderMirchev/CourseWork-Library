#ifndef EXECUTE_H
#define EXECUTE_H

#include <functional>

#include "../repositories/RepositoryExceptions.cpp"
#include "../services/ServiceExceptions.cpp"

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
}

template <class Result, class Function>
Result execute(const Function &function, const std::string &specifier)
{
    try
    {
        return function();
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
