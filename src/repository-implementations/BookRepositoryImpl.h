#ifndef BOOKPOSITORYIMPL_H
#define BOOKPOSITORYIMPL_H

#include "EntitySerializer.h"

#include "../repositories/BookRepository.h"

/**
 * Implementation of BookRepository
*/
class BookRepositoryImpl : public BookRepository
{

private:
    std::optional<EntitySerializer<Book>> serializer;
    std::vector<Book> books;

public:
    void setSource(const std::string &filename) override;
    void fetch() override;
    void removeSource() override;
    void saveChanges() const override;
    const std::vector<Book> &getAllBooks() const override;
    const std::optional<Book> getBookByISBN(const std::string &ISBN) const override;
    void addBook(
        const std::string &ISBN, const std::string &propertiesInCSV) override;
    void removeBook(const std::string &ISBN) override;

    BookRepositoryImpl() {}
};
#endif
