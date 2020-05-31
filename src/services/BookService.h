#ifndef BOOKSERVICE_H
#define BOOKSERVICE_H

#include <optional>
#include <string>
#include <vector>

#include "../entities/Book.h"

/**
 * Service interface for actions with books
*/
class BookService
{

public:
    virtual ~BookService() = default;

    /**
     * Opens file with filename and loads book data
     * 
     * Throws FileAlreadyOpenedException
     * Throws UnreadableFileException
    */
    virtual void openFile(const std::string &fileName) = 0;

    /**
     * Closes the file without saving.
     * 
     * Throws NoOpenFileException 
    */
    virtual void closeFile() = 0;

    /**
     * Writes current data to current opened file.
     * 
     * Throws NoOpenFileException if no file is open.
    */
    virtual void saveFile() const = 0;

    /**
     * Writes current data to new file and sets it as current opened
     * 
     * Throws NoOpenFileException
    */
    virtual void saveFileAs(const std::string &newFileName) = 0;

    /**
     * Returns all books.
     * 
     * Throws NoOpenFileException if no file is open.
    */
    virtual const std::vector<Book> getAllBooks() const = 0;

    /**
     * Returns optional value of book by ISBN.
     * 
     * Throws NoOpenFileException if no file is open.
    */
    virtual const std::optional<Book> getBookInfo(const std::string &ISBN) const = 0;

    /**
     * Returns all books that have optionString as their option value
     * Supported options: title, author, tag
     * 
     * Throws NoOpenFileException if no file is open.
     * Throws InvalidOptionException if option is not a valid field.
    */
    virtual const std::vector<Book> findBooksBy(
        const std::string &option, const std::string &optionString) const = 0;

    /**
     * Returns all books sorted by option in ascending/descending order
     * Supported options: title, author, year, rating
     * 
     * Throws NoOpenFileException if no file is open.
     * Throws InvalidOptionException if option is not a valid field.
    */
    virtual const std::vector<Book> sortBooksBy(
        const std::string &option, const std::string &order) = 0;

    /**
     * Returns all books sorted by option in ascending order
     * Supported options: title, author, year, rating
     * 
     * Throws NoOpenFileException if no file is open.
     * Throws InvalidOptionException if option is not a valid field.
    */
    virtual const std::vector<Book> sortBooksBy(const std::string &option) = 0;

    /**
     * Adds a book generated from csvProperties with unique value ISBN
     * 
     * Throws NoOpenFileException if no file is open.
     * Throws AlreadyExistsException
    */
    virtual void addBook(
        const std::string &ISBN, const std::string &csvProperties) = 0;

    /**
     * Removes a book by ISBN
     * 
     * Throws NoOpenFileException if no file is open.
     * Throws NotFoundException
    */
    virtual void removeBook(const std::string &ISBN) = 0;
};
#endif
