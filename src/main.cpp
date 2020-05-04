#include "repository-implementations/BookRepositoryImpl.h"
#include "repository-implementations/UserRepositoryImpl.h"

#include "service-impl/BookServiceImpl.h"
#include "service-impl/UserServiceImpl.h"

#include "user-interface/Controller.h"

#include <iostream>

int main()
{
    Controller controller(
        std::unique_ptr<UserService>(
            new UserServiceImpl(std::unique_ptr<UserRepository>(new UserRepositoryImpl("data.txt")))),
        std::unique_ptr<BookService>(
            new BookServiceImpl(std::unique_ptr<BookRepository>(new BookRepositoryImpl)))
    );

    return 0;
}