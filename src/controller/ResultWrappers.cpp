#include "ResultWrappers.h"

#include <iostream>

BookResult::BookResult(const Book &book) : book{book} {}

void BookResult::display() const
{
    this->book.print();
}

BookListResult::BookListResult(const std::vector<Book> &bookList)
    : bookList{bookList} {}

BookListResult::BookListResult(const std::vector<Book> &bookList,
                               const std::string &option)
    : bookList{bookList}, option{option} {}

void BookListResult::display() const
{
    for (const Book &book : this->bookList)
    {
        book.print(option);
    }
}

StringResult::StringResult(const std::string &string) : string{string} {}

void StringResult::display() const
{
    std::cout << this->string << std::endl;
}

UserLoginResult::UserLoginResult(const User &user) : user{user} {}

void UserLoginResult::display() const
{
    std::cout << "You are logged in as "
              << user.getUsername() << std::endl;
}

const User &UserLoginResult::getUser() const
{
    return this->user;
}
