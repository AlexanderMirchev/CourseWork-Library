#ifndef RESULTWRAPPERS_H
#define RESULTWRAPPERS_H

#include <iostream>
#include <memory>
#include "../entities/Book.h"
#include "../entities/User.h"

/*
    Classes expressing printable results(wrappers on entities/standard classes)
*/

/*
    Displayable Result interface
*/
class Result
{
public:
    virtual ~Result() = default;

    virtual void display() const = 0;
};

/*
    Wrapper for a single book
*/
class BookResult : public Result
{
private:
    Book book;

public:
    BookResult(const Book &book) : book{book} {}

    void display() const override
    {
        this->book.print();
    }
};

/*
    Wrapper for list of books
*/
class BookListResult : public Result
{
private:
    std::vector<Book> bookList;
    std::string option;

public:
    BookListResult(const std::vector<Book> &bookList) : bookList{bookList} {}
    BookListResult(const std::vector<Book> &bookList,
                   const std::string &option)
        : bookList{bookList}, option{option} {}

    void display() const override
    {
        for (const Book &book : this->bookList)
        {
            book.print(option);
        }
    }
};

/*
    Wrapper for a string message
*/
class StringResult : public Result
{
private:
    std::string string;

public:
    StringResult(const std::string &string) : string{string} {}

    void display() const override
    {
        std::cout << this->string << std::endl;
    }
};

class UserLoginResult : public Result
{
private:
    User user;

public:
    UserLoginResult(const User &user) : user{user} {}

    void display() const override
    {
        std::cout << "You are logged in as "
                  << user.getUsername() << std::endl;
    }
    const User &getUser() const
    {
        return this->user;
    }
};
#endif
