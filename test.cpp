#include <iostream>
#include <string>
#include "Book.h"
#include "User.h"

int main() {
    Book book = Book(std::string("kur"), std::string("kur"), 
        std::string("kur"), std::string("kur"), 2000, 
        std::vector<std::string> {"kur", "kur"}, 2, std::string("kur0000") );
    Book book1 = book;
    User user = User(std::string("kurvi"), std::string("belo"), User::Role::ADMIN);
    std::cout << std::boolalpha << user.isAdmin() << std::endl;
    return 0;
}