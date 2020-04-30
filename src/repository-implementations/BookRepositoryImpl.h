#ifndef _BOOKPOSITORYIMPL_HH
#define _BOOKPOSITORYIMPL_HH

#include "EntitySerializer.h"

#include "../repositories/BookRepository.h"

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

    const std::optional<const Book&> &getBookByISBN(const std::string &ISBN) const override;

    BookRepositoryImpl() {}
};
#endif
