#ifndef _BOOK_H
#define _BOOK_H

#include <string>
#include <vector>

#include "Serializable.h"

/**
 * An entity class for a book
*/
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

    /**
     * Detailed output for book
    */
    void print() const;
    /**
     * One line output with default output of author title and ISBN
     * Depending on string could add year/tag/rating
    */
    void print(const std::string &) const;

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
    Book(const Book &) = default;
    ~Book() = default;
    Book &operator=(const Book &) = default;
    Book(Book &&);
    Book &operator=(Book &&);
};
#endif
