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
    catch (const std::exception &e)
    {
        throw BadFormatException();
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

void BookRepositoryImpl::addBook(
    const std::string &ISBN, const std::string &propertiesInCSV)
{
    if (!this->serializer.has_value())
    {
        throw NoSourceException();
    }
    for (const Book &book : this->books)
    {
        if (book.getISBN() == ISBN)
        {
            throw EntityAlreadyExistsException();
        }
    }
    Book newBook;
    newBook.stringToObject(propertiesInCSV);
    this->books.push_back(newBook);
}

void BookRepositoryImpl::removeBook(const std::string &ISBN)
{
    if (!this->serializer.has_value())
    {
        throw NoSourceException();
    }
    std::vector<Book>::iterator iter;
    for (iter = this->books.begin(); iter < this->books.end(); iter++)
    {
        if (iter->getISBN() == ISBN)
        {
            this->books.erase(iter);
            return;
        }
    }
    throw EntityNotFoundException();
}
