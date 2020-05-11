#ifndef _BOOK_H
#define _BOOK_H

#include <string>
#include <vector>

#include "Serializable.h"

class Book : public Serializable
{

private:
    std::string author;
    std::string title;
    std::string genre;
    std::string description;
    int year;
    std::vector<std::string> tags;
    double rating;
    std::string ISBN;

public:
    /*
        See Serializable
    */
    const std::string objToString() const override;
    void stringToObject(const std::string &) override;

    /*
        Outputs to console

        param detailed - boolean value to determine whether to print all 
        of the book's characteristics or just basic information
    */
    void print(bool detailed) const;

    /*
        Getters
    */
    const std::string &getTitle() const;
    const std::string &getAuthor() const;
    const int &getYear() const;
    const std::vector<std::string> &getTags() const;
    const double &getRating() const;
    const std::string &getISBN() const;

    Book(const std::string &, const std::string &, const std::string &,
         const std::string &, const int, const std::vector<std::string> &,
         const double, const std::string &);
    Book();

    /*
        Default memory management
    */
    Book(const Book &) = default;
    ~Book() = default;
    Book &operator=(const Book &) = default;

    /*
        Move operators
    */
    Book(Book &&);
    Book &operator=(Book &&);
};
#endif
