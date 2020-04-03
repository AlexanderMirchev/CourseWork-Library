#ifndef _BOOK_H
#define _BOOK_H

#include <string>
#include <vector>

class Book
{
private:
   std::string author;
   std::string title;
   std::string genre;/* could be different type/enum */
   std::string description;
   unsigned int year;
   std::vector<std::string> keyWords;
   unsigned int rating;/* could be enumeration/char */
   std::string ISBN;
   
public:
    Book(const std::string&, const std::string&, const std::string&, 
        const std::string&, const unsigned int, const std::vector<std::string>&, 
        const unsigned int, const std::string&);
    Book(const Book&);
    Book(Book&&);
    ~Book() = default;

    Book& operator= (const Book&);
    Book& operator= (Book&&);

private:
    void copy(const Book&);
    void copy(const std::string&, const std::string&, const std::string&, 
        const std::string&, const unsigned int, const std::vector<std::string>&, 
        const unsigned int, const std::string&);
};
#endif
