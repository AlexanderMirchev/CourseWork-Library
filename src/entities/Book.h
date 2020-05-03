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
    const std::string objToString() const override;

    void stringToObject(const std::string &) override;

    /*
        Returns title string
    */
    const std::string &getTitle() const;

    /*
        Returns author name string
    */
    const std::string &getAuthor() const;

    /*
        Returns the year the book was published
    */
    const int getYear() const;

    /*
        Returns vector of tags
    */
    const std::vector<std::string> &getTags() const;

    /*
        Returns the rating of the book
    */
    const double getRating() const;

    /*
        Returns ISBN string
    */
    const std::string &getISBN() const;

    /*
        Outputs to console
    */
    void print(bool detailed) const;

    Book(const std::string &, const std::string &, const std::string &,
         const std::string &, const int, const std::vector<std::string> &,
         const double, const std::string &);

    Book();

    Book(const Book &) = default;

    ~Book() = default;

    Book &operator=(const Book &) = default;

    Book(Book &&);

    Book &operator=(Book &&);
};
#endif
