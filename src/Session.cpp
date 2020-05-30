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
            std::string username, password;
            std::cout << "Username: ";
            std::getline(std::cin, username);
            std::cout << "Password: ";
            std::getline(std::cin, password);

            command.push_back(username);
            command.push_back(password);
            const std::unique_ptr<Result> result =
                controller.runCommand(command, loggedUser);
            try
            {
                const UserLoginResult *res =
                    dynamic_cast<UserLoginResult *>(result.get());
                if(res ==  nullptr) {
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
        if (shouldExecute)
        {
            Console::display(controller.runCommand(command, loggedUser));
        }
    }
}