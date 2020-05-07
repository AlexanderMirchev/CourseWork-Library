#include "BookRepositoryImpl.h"

#include "../repositories/RepositoryExceptions.cpp"

void BookRepositoryImpl::setSource(const std::string &filename)
{

    if (this->serializer.has_value())
    {
        throw SourceAlreadyExistsException();
    }

    this->serializer = EntitySerializer<Book>(filename);
}
void BookRepositoryImpl::fetch()
{
    if (!this->serializer.has_value())
    {
        throw NoSourceException();
    }
    try
    {
        this->books = this->serializer.value().readAllEntities();
    }
    catch(const std::exception& e)
    {
        throw BadFileException();
        this->serializer = std::nullopt;
    }
}
void BookRepositoryImpl::removeSource()
{

    if (!this->serializer.has_value())
    {
        throw NoSourceException();
    }

    this->serializer = std::nullopt;
}
void BookRepositoryImpl::saveChanges() const
{

    if (!this->serializer.has_value())
    {
        throw NoSourceException();
    }

    this->serializer.value().writeAllEntities(this->books);
}

const std::vector<Book> &BookRepositoryImpl::getAllBooks() const
{

    if (!this->serializer.has_value())
    {
        throw NoSourceException();
    }

    return this->books;
}
const std::optional<Book> BookRepositoryImpl::getBookByISBN(const std::string &ISBN) const
{

    if (!this->serializer.has_value())
    {
        throw NoSourceException();
    }

    for (const Book &book : this->books)
    {
        if (book.getISBN() == ISBN)
        {
            return book;
        }
    }
    return std::nullopt;
}
