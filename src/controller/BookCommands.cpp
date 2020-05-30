#include "Controller.h"
#include <cassert>

std::unique_ptr<Result> Controller::books(
    const std::vector<std::string> &commands, const UserRole &role)
{
    const unsigned int numberOfWords = commands.size();
    assert(numberOfWords > 1);

    if (commands[1] == "all")
    {
        return validateAndExecute(
            [this] {
                return booksAll();
            },
            USER, role, Controller::TWO_WORDS, numberOfWords);
    }
    if (commands[1] == "info")
    {
        return validateAndExecute(
            [this, commands] {
                return booksInfo(commands[2]);
            },
            USER, role, Controller::THREE_WORDS, numberOfWords);
    }
    if (commands[1] == "find")
    {
        return validateAndExecute(
            [this, commands] {
                return booksFind(commands[2],
                                 commands[3]);
            },
            USER, role, Controller::FOUR_WORDS, numberOfWords);
    }
    if (commands[1] == "sort")
    {
        if (numberOfWords == 3)
        {
            return validateAndExecute(
                [this, commands] {
                    return booksSort(commands[2]);
                },
                USER, role, THREE_WORDS, numberOfWords);
        }
        return validateAndExecute(
            [this, commands] {
                return booksSort(commands[2],
                                 commands[3]);
            },
            USER, role, FOUR_WORDS, numberOfWords);
    }
    return std::unique_ptr<Result>(new StringResult(INVALID_COMMAND));
}

std::unique_ptr<Result> Controller::booksAll() const
{
    std::vector<Book> books = this->bookService->getAllBooks();
    if (books.size() == 0)
    {
        return std::unique_ptr<Result>(new StringResult("No books found."));
    }
    return std::unique_ptr<Result>(new BookListResult(books));
}
std::unique_ptr<Result> Controller::booksInfo(const std::string &ISBN) const
{
    std::optional<Book> book = this->bookService->getBookInfo(ISBN);
    if (book.has_value())
    {
        return std::unique_ptr<Result>(new BookResult(book.value()));
    }
    return std::unique_ptr<Result>(new StringResult("Book not found."));
}
std::unique_ptr<Result> Controller::booksFind(
    const std::string &option, const std::string &optionString)
{
    std::vector<Book> books = this->bookService->findBooksBy(option, optionString);
    if (books.size() == 0)
    {
        return std::unique_ptr<Result>(new StringResult(
            "No books with the given criteria found."));
    }
    return std::unique_ptr<Result>(new BookListResult(books));
}
std::unique_ptr<Result> Controller::booksSort(
    const std::string &option, const std::string &order)
{
    std::vector<Book> books = this->bookService->sortBooksBy(option, order);
    if (books.size() == 0)
    {
        return std::unique_ptr<Result>(new StringResult("No books to sort."));
    }
    return std::unique_ptr<Result>(new BookListResult(books));
}
std::unique_ptr<Result> Controller::booksSort(const std::string &option)
{
    std::vector<Book> books = this->bookService->sortBooksBy(option, "asc");
    if (books.size() == 0)
    {
        return std::unique_ptr<Result>(new StringResult("No books to sort."));
    }
    return std::unique_ptr<Result>(new BookListResult(books));
}
