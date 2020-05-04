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
    // try
    this->books = this->serializer.value().readAllEntities();
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

// const std::vector<Book> &BookRepositoryImpl::getAllBooksSortedBy(
//     const std::function<bool(const Book &, const Book &)> &fieldComparator, bool asc)
// {
//     std::vector<Book> booksNewOrder(this->books);
//     for (size_t i = 0; i < booksNewOrder.size(); i++)
//     {
//         for (size_t j = 0; j < booksNewOrder.size() - i - 1; j++)
//         {
//             if (fieldComparator(booksNewOrder[j], booksNewOrder[j - 1]) == asc)
//             {
//                 std::swap(booksNewOrder[j], booksNewOrder[j + 1]);
//             }
//         }
//     }
//     this->books = booksNewOrder;
//     return this->books;
// }

