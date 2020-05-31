#ifndef RESULTWRAPPERS_H
#define RESULTWRAPPERS_H

#include "../entities/Book.h"
#include "../entities/User.h"

/**
 * Classes expressing printable results(wrappers on entities/standard classes)
*/

/**
 * Displayable Result interface
*/
class Result
{
public:
    virtual ~Result() = default;

    /**
     * Displays the content of the result
    */
    virtual void display() const = 0;
};

/**
 * Result wrapper for a single book
*/
class BookResult : public Result
{
private:
    Book book;

public:
    BookResult(const Book &book);

    void display() const override;
};

/**
 * Result wrapper for list of books
*/
class BookListResult : public Result
{
private:
    std::vector<Book> bookList;
    std::string option;

public:
    BookListResult(const std::vector<Book> &bookList);

    /**
     * Constructor with option string to print the content accordingly
    */
    BookListResult(const std::vector<Book> &bookList,
                   const std::string &option);

    void display() const override;
};

/**
 * Result wrapper for a string
*/
class StringResult : public Result
{
private:
    std::string string;

public:
    StringResult(const std::string &string);

    void display() const override;
};

/**
 * Result wrapper for a succesfully authenticated user
*/
class UserLoginResult : public Result
{
private:
    User user;

public:
    UserLoginResult(const User &user);

    void display() const override;

    /**
     * Returns the authenticated user
    */
    const User &getUser() const;
};

#endif