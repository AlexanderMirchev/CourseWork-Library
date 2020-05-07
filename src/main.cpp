#include "repository-implementations/BookRepositoryImpl.h"
#include "repository-implementations/UserRepositoryImpl.h"

#include "service-impl/BookServiceImpl.h"
#include "service-impl/UserServiceImpl.h"

#include "user-interface/Controller.h"
#include "user-interface/Console.h"

#include <iostream>

int main()
{
    Controller controller(
        std::unique_ptr<UserService>(
            new UserServiceImpl(std::unique_ptr<UserRepository>(new UserRepositoryImpl("data.txt")))),
        std::unique_ptr<BookService>(
            new BookServiceImpl(std::unique_ptr<BookRepository>(new BookRepositoryImpl)))
    );
    while (true)
    {
        std::string line;
        std::getline(std::cin, line);

        std::vector<std::string> command = Console::readInput(line);
        if(command.size() == 1 && command[0] == "login" && !controller.hasLoggedUser()) {
            std::string username, password;
            std::cout << "Username: ";
            std::cin >> username;
            std::cout << "Password: ";
            std::cin >> password;

            command.push_back(username);
            command.push_back(password);
        }
        if(command.size() == 1 && command[0] == "exit") {
            break;
        }
        
        Console::display(controller.runCommand(command));
    }

    return 0;
}