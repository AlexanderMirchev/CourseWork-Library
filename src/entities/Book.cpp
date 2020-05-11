#include <iostream>
#include "Book.h"
#include "../repositories/RepositoryExceptions.cpp"

const std::string Book::objToString() const
{

    std::string result;

    result.append(title + ',');
    result.append(author + ',');
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
    const size_t minimalRequiredSize = 9;
    if (values.size() < minimalRequiredSize)
    {
        throw BadFormatException();
    }
    
    unsigned int iterator = 0;

    this->title = values[iterator++];
    this->author = values[iterator++];
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
void Book::print(bool detailed) const
{
    if (detailed)
    {
        std::cout << "Title: " << this->title;
        std::cout << "\nAuthor: " << this->author;
        std::cout << "\nYear: " << this->year;
        std::cout << "\nGenre: " << this->genre;
        std::cout << "\nDescription: " << this->description;
        std::cout << "\nTags: ";
        for (const std::string &tag : this->tags)
        {
            std::cout << tag << " ";
        }
        std::cout << "\nRating: " << this->rating;
        std::cout << "\nISBN: " << this->ISBN << std::endl;
    }
    else
    {
        std::cout << this->title << " by "
                  << this->author << " " << this->ISBN << std::endl;
    }
}

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

const std::string &Book::getTitle() const
{
    return this->title;
}
const std::string &Book::getAuthor() const
{
    return this->author;
}
const int &Book::getYear() const
{
    return this->year;
}
const std::vector<std::string> &Book::getTags() const
{
    return this->tags;
}
const double &Book::getRating() const
{
    return this->rating;
}
const std::string &Book::getISBN() const
{
    return this->ISBN;
}
