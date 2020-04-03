#include "Book.h"
#include <iostream>

Book::Book(const std::string& author, const std::string& title, const std::string& genre, 
    const std::string& description, const unsigned int year, const std::vector<std::string>& keyWords, 
    const unsigned int rating, const std::string& ISBN) {

        copy(author, title, genre, description, year, keyWords, rating, ISBN);
}
Book::Book(const Book& book) {
    copy(book);
}
Book::Book(Book&& book) {
    std::move(book);
}
Book::~Book() {
    std::cout << "deleting" << std::endl;
}
Book& Book::operator= (const Book& book) {
    copy(book);
    return *this;
}
Book& Book::operator= (Book&& book) {
    std::move(book);
}

void Book::copy(const Book& book) {
    copy(book.author, book.title, book.genre, book.description, 
        book.year, book.keyWords, book.rating, book.ISBN);
}
void Book::copy(const std::string& author, const std::string& title, const std::string& genre, 
    const std::string& description, const unsigned int year, const std::vector<std::string>& keyWords, 
    const unsigned int rating, const std::string& ISBN) {
        this->author = author;
        this->title = title;
        this->genre = genre;
        this->description = description;
        this->year = year;
        this->keyWords = keyWords;
        this->rating = rating;
        this->ISBN = ISBN;
}
