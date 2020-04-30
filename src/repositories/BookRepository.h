#ifndef _BOOKREPOSITORY_HH
#define _BOOKREPOSITORY_HH

#include <functional>
#include <optional>
#include <string>
#include <vector>

#include "../entities/Book.h"

class BookRepository
{

public:
    virtual ~BookRepository();

    /*
        Sets input/output file for repository.
        Throws SourceAlreadyExistsException if there is a file already open
    */
    virtual void setSource(const std::string &) = 0;

    /*
        Gets all entities from source file.
        Throws NoSourceException if no file is opened.
        Throws ??
    */
    virtual void fetch() = 0;

    /*
        Removes current input/output file.
        Throws NoSourceException if no file is opened.
    */
    virtual void removeSource() = 0;

    /*
        Writes current list of books to file.
        Throws NoSourceException if no file is opened.
    */
    virtual void saveChanges() const = 0;

    /*
        Returns all books.
        Throws NoSourceException if no file is opened.
    */
    virtual const std::vector<Book> &getAllBooks() const = 0;

    /*
        Returns book by ISBN.
        If no match is found nullopt is returned.
        Throws NoSourceException if no file is opened.
    */
    virtual const std::optional<const Book &> &getBookByISBN(const std::string &ISBN) const = 0;
};
#endif
