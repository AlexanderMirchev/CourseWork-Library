#ifndef RESULTWRAPPERS_H
#define RESULTWRAPPERS_H

#include <iostream>
#include <memory>
#include "../entities/Book.h"

class Result
{
public:
    virtual ~Result() = default;

    virtual void display() const = 0;
};

class BookResult : public Result
{
private:
    Book book;

public:
    BookResult(const Book &book) : book{std::move(book)} {}

    void display() const override
    {
        this->book.print(true);
    }
};

class BookListResult : public Result
{
private:
    std::vector<Book> bookList;

public:
    BookListResult(const std::vector<Book> &bookList) : bookList{std::move(bookList)} {}

    void display() const override
    {
        for (const Book &book : this->bookList)
        {
            book.print(false);
        }
    }
};

class StringResult : public Result
{
private:
    std::string string;

public:
    StringResult(const std::string& string) : string{string} {}
    StringResult(std::string &&string) : string{std::move(string)} {}

    void display() const override
    {
        std::cout << this->string << std::endl;
    }
};
#endif
