#ifndef BOOKREPOSITORY_H
#define BOOKREPOSITORY_H

#include <functional>
#include <optional>
#include <string>
#include <vector>

#include "../entities/Book.h"

/**
 * Interface for CRUD operations for books
*/
class BookRepository
{

public:
    virtual ~BookRepository() = default;

    /**
     * Sets input/output file for repository.
     * 
     * Throws SourceAlreadyExistsException if there is a file already open
    */
    virtual void setSource(const std::string &) = 0;

    /**
     * Gets all entities from source file.
     * 
     * Throws NoSourceException if no file is opened.
     * Throws BadFormatException if the file does not meet the book requirements
    */
    virtual void fetch() = 0;

    /**
     * Removes current input/output file.
     * 
     * Throws NoSourceException if no file is opened.
    */
    virtual void removeSource() = 0;

    /**
     * Writes current list of books to file.
     * 
     * Throws NoSourceException if no file is opened.
    */
    virtual void saveChanges() const = 0;

    /**
     * Returns all books.
     * 
     * Throws NoSourceException if no file is opened.
    */
    virtual const std::vector<Book> &getAllBooks() const = 0;

    /**
     * Returns optional value of book by ISBN.
     * 
     * Throws NoSourceException if no file is opened.
    */
    virtual const std::optional<Book> getBookByISBN(const std::string &ISBN) const = 0;

    /**
     * Adds a book(generated from CSV string) to current list of books 
     * if ISBN is unique
     * 
     * Throws EntityAlreadyExistsException
     * Throws NoSourceException if no file is opened.
    */
    virtual void addBook(
        const std::string &ISBN, const std::string &propertiesInCSV) = 0;

    /**
     * Removes a book from current list of books if ISBN match is found
     * 
     * Throws EntityNotFoundException
     * Throws NoSourceException if no file is opened.
    */
    virtual void removeBook(const std::string &ISBN) = 0;
};
#endif
