#include "Session.h"

#include "repository-implementations/BookRepositoryImpl.h"
#include "repository-implementations/UserRepositoryImpl.h"

#include "service-impl/BookServiceImpl.h"
#include "service-impl/UserServiceImpl.h"

#include "user-interface/Console.h"

Session::Session()
    : controller{std::unique_ptr<UserService>(
                     new UserServiceImpl(
                         std::unique_ptr<UserRepository>(
                             new UserRepositoryImpl("data.txt")))),
                 std::unique_ptr<BookService>(
                     new BookServiceImpl(
                         std::unique_ptr<BookRepository>(
                             new BookRepositoryImpl)))} {}

std::pair<std::string, std::string> inputUser();
std::pair<std::string, std::string> inputBook();
void Session::start()
{
    bool shouldContinue = true;
    while (shouldContinue)
    {
        std::string line;
        std::cout << "~ ";
        std::getline(std::cin, line);

        std::vector<std::string> command = Console::readInput(line);
        bool shouldExecute = true;
        if (command.size() == 1 && command[0] == "login")
        {
            std::pair<std::string, std::string> userData = inputUser();
            command.push_back(userData.first);
            command.push_back(userData.second);
            const std::unique_ptr<Result> result =
                controller.runCommand(command, loggedUser);
            try
            {
                const UserLoginResult *res =
                    dynamic_cast<UserLoginResult *>(result.get());
                if (res == nullptr)
                {
                    throw std::bad_cast();
                }
                this->loggedUser = res->getUser();
            }
            catch (const std::bad_cast &e)
            {
            }
            Console::display(result);
            shouldExecute = false;
        }
        if (command.size() == 1 && command[0] == "logout")
        {
            std::string message;
            if (this->loggedUser.has_value())
            {
                this->loggedUser = std::nullopt;
                message = "Successfully logged out";
            }
            else
            {
                message = "You can't log out when you are not logged in";
            }
            Console::display(std::unique_ptr<Result>(new StringResult(message)));
            shouldExecute = false;
        }
        if (command.size() == 1 && command[0] == "exit")
        {
            shouldContinue = false;
            shouldExecute = false;
        }
        if (command.size() == 2 && command[0] == "books" && command[1] == "add")
        {
            std::pair<std::string, std::string> bookData = inputBook();
            command.push_back(bookData.first);
            command.push_back(bookData.second);
        }
        if (shouldExecute)
        {
            Console::display(controller.runCommand(command, loggedUser));
        }
    }
}

std::pair<std::string, std::string> inputUser()
{
    std::string username, password;
    std::cout << "Username: ";
    std::getline(std::cin, username);
    std::cout << "Password: ";
    std::getline(std::cin, password);
    return std::pair<std::string, std::string>(username, password);
}
std::pair<std::string, std::string> inputBook()
{
    std::string author;
    std::cout << "Author: ";
    std::getline(std::cin, author);
    std::string title;
    std::cout << "Title: ";
    std::getline(std::cin, title);
    std::string genre;
    std::cout << "Genre: ";
    std::getline(std::cin, genre);
    std::string description;
    std::cout << "Description: ";
    std::getline(std::cin, description);
    std::string year;
    std::cout << "Year: ";
    std::getline(std::cin, year);
    std::string tags;
    std::cout << "Tags(separared by commas): ";
    std::getline(std::cin, tags);
    std::string rating;
    std::cout << "Rating: ";
    std::getline(std::cin, rating);
    std::string ISBN;
    std::cout << "ISBN: ";
    std::getline(std::cin, ISBN);

    std::string properties;

    properties.append(title + ',');
    properties.append(author + ',');
    properties.append(genre + ',');
    properties.append(description + ',');
    properties.append(year + ',');
    properties.append(tags + ',');
    properties.append(rating + ',');
    properties.append(ISBN);

    return std::pair<std::string, std::string>(ISBN, properties);
}