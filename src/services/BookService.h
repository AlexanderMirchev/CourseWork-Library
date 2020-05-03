#ifndef BOOKSERVICE_H
#define BOOKSERVICE_H

#include <optional>
#include <string>
#include <vector>

#include "../entities/Book.h"

class BookService
{

public:
    virtual ~BookService() = default;

    /*
        Sets file to fetch book data.

        -param fileName: name of file to be opened

        Throws FileAlreadyOpenedException if file is already open.
    */
    virtual void openFile(const std::string &fileName) = 0;

    /*
        Closes the file without saving.

        Throws NoOpenFileException if no file is open.
    */
    virtual void closeFile() = 0;

    /*
        Writes current data to current opened file.

        Throws NoOpenFileException if no file is open.
    */
    virtual void saveFile() const = 0;

    /*
        Writes current data to new file

        -param newFileName: name of new file(address)

        Throws NoOpenFileException if no file is open.
    */
    virtual void saveFileAs(const std::string &newFileName) = 0;

    /*
        Returns all books.

        Throws NoOpenFileException if no file is open.
    */
    virtual const std::vector<Book> &getAllBooks() const = 0;

    /*
        Returns optional of type book by ISBN.

        Throws NoOpenFileException if no file is open.
    */
    virtual const std::optional<Book> &getBookInfo(const std::string &ISBN) const = 0;

    /*
        Returns all books that have optionString as their option value for a certain option

        Throws NoOpenFileException if no file is open.
        Throws InvalidOptionException if option is not a valid field.
    */
    virtual const std::vector<Book> findBooksBy(
        const std::string &option, const std::string &optionString) const = 0;

    /*
        Returns all books sorted by option in ascending/descending order

        Throws NoOpenFileException if no file is open.
        Throws InvalidOptionException if option is not a valid field.
    */
    virtual const std::vector<Book> sortBooksBy(
        const std::string &option, const std::string &ascdesc);

    /*
        Returns all books sorted by option in ascending(by default) order

        Throws NoOpenFileException if no file is open.
        Throws InvalidOptionException if option is not a valid field.
    */
    virtual const std::vector<Book> sortBooksBy(const std::string &option);
};
#endif
