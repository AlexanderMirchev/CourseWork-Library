// #include <iostream>
#include "Book.h"

Book::Book(const std::string &author, const std::string &title, const std::string &genre,
           const std::string &description, const int year, const std::vector<std::string> &tags,
           const double rating, const std::string &ISBN)
{
    this->author = author;
    this->title = title;
    this->genre = genre;
    this->description = description;
    this->year = year;
    this->tags = tags;
    this->rating = rating;
    this->ISBN = ISBN;
}
Book::Book() : Book(std::string(""), std::string(""), std::string(""), std::string(""),
                    0, std::vector<std::string>{}, 0, std::string("")) {}
Book::Book(Book &&other)
{
    *this = other;
}
Book &Book::operator=(Book &&other)
{
    this->author = std::move(other.author);
    this->title = std::move(other.title);
    this->genre = std::move(other.genre);
    this->description = std::move(other.description);
    this->year = std::move(other.year);
    this->tags = std::move(other.tags);
    this->rating = other.rating;
    this->ISBN = std::move(other.ISBN);
    return *this;
}
const std::string Book::objToString() const
{

    std::string result;

    result.append(author + ',');
    result.append(title + ',');
    result.append(genre + ',');
    result.append(description + ',');
    result.append(std::to_string(year) + ',');
    for (const std::string &word : tags)
    {
        result.append(word + ',');
    }
    result.append(std::to_string(rating) + ',');
    result.append(ISBN);

    return result;
}
void Book::stringToObject(const std::string &string)
{
    std::vector<std::string> values = separateCSVs(string);

    int iterator = 0;

    this->author = values[iterator++];
    this->title = values[iterator++];
    this->genre = values[iterator++];
    this->description = values[iterator++];
    this->year = std::stoi(values[iterator++]);
    std::vector<std::string> newTags;
    while (iterator < values.size() - 2)
    {
        newTags.push_back(values[iterator++]);
    }
    this->tags = newTags;
    this->rating = std::stod(values[iterator++]);
    this->ISBN = values[iterator++];
}

// std::ostream& operator << (std::ostream& out, const Book& book) {
//     out << book.author << std::endl;
//     out << book.title << std::endl;
//     out << book.genre << std::endl;
//     out << book.description << std::endl;
//     out << book.year << std::endl;
//     for(const std::string& str: book.tags) {
//         out << str << std::endl;
//     }
//     out << book.rating << std::endl;
//     out << book.ISBN << std::endl;
// }

const std::string &Book::getTitle() const
{
    return this->title;
}

const std::string &Book::getAuthor() const
{
    return this->author;
}
const int Book::getYear() const
{
    return this->year;
}
const std::vector<std::string> &Book::getTags() const
{
    return this->tags;
}
const double Book::getRating() const
{
    return this->rating;
}
const std::string &Book::getISBN() const
{
    return this->ISBN;
}