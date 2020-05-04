#include "Controller.h"
Controller::Controller(std::unique_ptr<UserService> &&userService,
                       std::unique_ptr<BookService> &&bookService)
    : userService{std::move(userService)},
      bookService{std::move(bookService)}, userRole(GUEST) {}
const std::unique_ptr<Result> Controller::runCommand(
    const std::vector<std::string> &extractedCommandIntoWords)
{
    if (extractedCommandIntoWords.empty())
    {
        return std::unique_ptr<Result>(new StringResult(INVALID_COMMAND));
    }

    const BaseCommand command = findCommand(extractedCommandIntoWords[0]);
    const size_t numberOfWords = extractedCommandIntoWords.size();

    switch (command)
    {
    case OPEN:
        return validateAndExecute(
            [this, extractedCommandIntoWords] {
                return open(extractedCommandIntoWords[1]);
            },
            GUEST, Controller::TWO_WORDS, numberOfWords);

    case CLOSE:
        return validateAndExecute(
            [this] {
                return close();
            },
            GUEST, Controller::ONE_WORD, numberOfWords);
    case SAVE:
        return validateAndExecute(
            [this] {
                return save();
            },
            GUEST, Controller::ONE_WORD, numberOfWords);
    case SAVEAS:
        return validateAndExecute(
            [this, extractedCommandIntoWords] {
                return saveas(extractedCommandIntoWords[1]);
            },
            GUEST, Controller::TWO_WORDS, numberOfWords);
    case HELP:
        return validateAndExecute(
            [this, extractedCommandIntoWords] {
                return help();
            },
            GUEST, Controller::ONE_WORD, numberOfWords);
    case LOGIN:
        return validateAndExecute(
            [this, extractedCommandIntoWords] {
                return login(extractedCommandIntoWords[1], extractedCommandIntoWords[2]);
            },
            GUEST, Controller::THREE_WORDS, numberOfWords);
    case LOGOUT:
        return validateAndExecute(
            [this] {
                return logout();
            },
            USER, Controller::ONE_WORD, numberOfWords);
    case BOOKS:
        if (numberOfWords > 1)
        {
            if (extractedCommandIntoWords[1] == "all")
            {
                return validateAndExecute(
                    [this] {
                        return booksAll();
                    },
                    USER, Controller::TWO_WORDS, numberOfWords);
            }
            if (extractedCommandIntoWords[1] == "find")
            {
                return validateAndExecute(
                    [this, extractedCommandIntoWords] {
                        return booksFind(extractedCommandIntoWords[2],
                                         extractedCommandIntoWords[3]);
                    },
                    USER, Controller::FOUR_WORDS, numberOfWords);
            }
            if (extractedCommandIntoWords[1] == "sort")
            {
                if (numberOfWords == 3)
                {
                    return validateAndExecute(
                        [this, extractedCommandIntoWords] {
                            return booksSort(extractedCommandIntoWords[2]);
                        },
                        USER, THREE_WORDS, numberOfWords);
                }
                return validateAndExecute(
                    [this, extractedCommandIntoWords] {
                        return booksSort(extractedCommandIntoWords[2],
                                         extractedCommandIntoWords[3]);
                    },
                    USER, FOUR_WORDS, numberOfWords);
            }
        }
        return std::unique_ptr<Result>(new StringResult(INVALID_COMMAND));
    case USERS:
        if (numberOfWords > 1)
        {
            if (extractedCommandIntoWords[1] == "add")
            {
                return validateAndExecute(
                    [this, extractedCommandIntoWords] {
                        return usersAdd(extractedCommandIntoWords[2],
                                        extractedCommandIntoWords[3]);
                    },
                    ADMIN, FOUR_WORDS, numberOfWords);
            }
            if (extractedCommandIntoWords[1] == "remove")
            {
                return validateAndExecute(
                    [this, extractedCommandIntoWords] {
                        return usersRemove(extractedCommandIntoWords[2]);
                    },
                    ADMIN, THREE_WORDS, numberOfWords);
            }
        }
        return std::unique_ptr<Result>(new StringResult(INVALID_COMMAND));
    default:
        return std::unique_ptr<Result>(new StringResult(INVALID_COMMAND));
    };
}

const Controller::StringToBaseCommandMap Controller::COMMAND_MAP = {
    {"open", OPEN},
    {"close", CLOSE},
    {"save", SAVE},
    {"saveas", SAVEAS},
    {"help", HELP},
    {"login", LOGIN},
    {"logout", LOGOUT},
    {"books", BOOKS},
    {"users", USERS}};
Controller::BaseCommand Controller::findCommand(const std::string &command)
{
    StringToBaseCommandMap::const_iterator mapEntry = COMMAND_MAP.find(command);
    if (mapEntry == COMMAND_MAP.end())
    {
        return InvalidCommand;
    }
    return mapEntry->second;
}

const std::unique_ptr<Result> Controller::validateAndExecute(
    const std::function<const std::unique_ptr<Result>()> &command,
    UserRole requiredRole, const size_t &requiredSize, const size_t &actualSize)
{
    // effective c++ solution to methods with same code but different qualifiers
    return std::as_const(*this)
        .validateAndExecute(command, requiredRole, requiredSize, actualSize);
}

const std::unique_ptr<Result> Controller::validateAndExecute(
    const std::function<const std::unique_ptr<Result>()> &command,
    UserRole requiredRole, const size_t &requiredSize, const size_t &actualSize) const
{
    if (requiredRole > this->userRole)
    {
        return std::unique_ptr<Result>(
            new StringResult("You are not authorized to perform this action."));
    }
    if (requiredSize != actualSize)
    {
        return std::unique_ptr<Result>(
            new StringResult("The amount of parameters does not match any function."));
    }
    try
    {
        return command();
    }
    catch (const ServiceException &e)
    {
        return std::unique_ptr<Result>(new StringResult(e.what()));
    }
    catch (const std::exception &e)
    {
        return std::unique_ptr<Result>(new StringResult("Unknown error."));
    }
}

const std::string Controller::INVALID_COMMAND = "No recognized command";

const std::string Controller::HELP_MESSAGE_GUEST =
    std::string("Help:\n open <filename> - opens file to read from\n ") +
    std::string("close - closes opened file\n save - saves current changes to file\n ") +
    std::string("saveas <filename> - saves current changes to given file\n ") +
    std::string("exit - exits the program\n login - login for user with username and password\n ");
const std::string Controller::HELP_MESSAGE_USER =
    HELP_MESSAGE_GUEST + std::string("logout - logouts the current user\n ") +
    std::string("books all - displays all books form file\n") +
    std::string("books info <ISBN> - displays the book with the given isbn\n ") +
    std::string("books find <option> <option string>") +
    std::string(" - finds all books by option(title, author, tag)\n ") +
    std::string("books sort <option> [asc/desc] + - sorts all books by ") +
    std::string("option(title,author, year, rating) in ascending descending order(optional)\n ");
const std::string Controller::HELP_MESSAGE_ADMIN =
    HELP_MESSAGE_USER +
    std::string("users add <username> <password> - creates new user with username and password\n ") +
    std::string("users remove <username> - removes user with username\n ");
const std::unique_ptr<Result> Controller::open(const std::string &filename)
{
    this->bookService->openFile(filename);
    this->openedFile = filename;
    return std::unique_ptr<Result>(new StringResult("File successfully opened."));
}
const std::unique_ptr<Result> Controller::close()
{
    this->bookService->closeFile();
    this->openedFile = std::nullopt;
    return std::unique_ptr<Result>(new StringResult("File successfully closed."));
}
const std::unique_ptr<Result> Controller::save() const
{
    this->bookService->saveFile();
    return std::unique_ptr<Result>(new StringResult("File successfully saved."));
}
const std::unique_ptr<Result> Controller::saveas(const std::string &filename)
{
    this->bookService->saveFileAs(filename);
    return std::unique_ptr<Result>(
        new StringResult("File successfully saved in new file."));
}
const std::unique_ptr<Result> Controller::help() const
{
    std::string message;
    switch (this->userRole)
    {
    case GUEST:
        message = HELP_MESSAGE_GUEST;
        break;
    case USER:
        message = HELP_MESSAGE_GUEST;
        break;
    case ADMIN:
        message = HELP_MESSAGE_ADMIN;
        break;
    default:
        break;
    }
    return std::unique_ptr<Result>(new StringResult(message));
}
const std::unique_ptr<Result> Controller::login(
    const std::string &username, const std::string &password)
{
    this->loggedUser = this->userService->authenticateUser(username, password);
    this->userRole = this->loggedUser->isAdmin() ? ADMIN : USER;

    return std::unique_ptr<Result>(new StringResult("Successfully logged in."));
}
const std::unique_ptr<Result> Controller::logout()
{
    this->loggedUser = std::nullopt;
    this->userRole = GUEST;
    return std::unique_ptr<Result>(new StringResult("Successfully logged out."));
}
const std::unique_ptr<Result> Controller::booksAll() const
{
    std::vector<Book> books = this->bookService->getAllBooks();
    if (books.size() == 0)
    {
        return std::unique_ptr<Result>(new StringResult("No books found."));
    }
    return std::unique_ptr<Result>(new BookListResult(books));
}
const std::unique_ptr<Result> Controller::booksInfo(const std::string &ISBN) const
{
    std::optional<Book> book = this->bookService->getBookInfo(ISBN);
    if (book.has_value())
    {
        return std::unique_ptr<Result>(new BookResult(book.value()));
    }
    return std::unique_ptr<Result>(new StringResult("Book not found."));
}
const std::unique_ptr<Result> Controller::booksFind(
    const std::string &option, const std::string &optionString)
{
    std::vector<Book> books = this->bookService->findBooksBy(option, optionString);
    if (books.size() == 0)
    {
        return std::unique_ptr<Result>(new StringResult(
            "No books with the given criteria found."));
    }
    return std::unique_ptr<Result>(new BookListResult(books));
}
const std::unique_ptr<Result> Controller::booksSort(
    const std::string &option, const std::string &order)
{
    std::vector<Book> books = this->bookService->sortBooksBy(option, order);
    if (books.size() == 0)
    {
        return std::unique_ptr<Result>(new StringResult("No books to sort."));
    }
    return std::unique_ptr<Result>(new BookListResult(books));
}
const std::unique_ptr<Result> Controller::booksSort(const std::string &option)
{
    std::vector<Book> books = this->bookService->sortBooksBy(option, "asc");
    if (books.size() == 0)
    {
        return std::unique_ptr<Result>(new StringResult("No books to sort."));
    }
    return std::unique_ptr<Result>(new BookListResult(books));
}
const std::unique_ptr<Result> Controller::usersAdd(
    const std::string &username, const std::string &password)
{
    this->userService->addUser(username, password);
    return std::unique_ptr<Result>(new StringResult("User successfully added."));
}
const std::unique_ptr<Result> Controller::usersRemove(const std::string &username)
{
    this->userService->removeUser(username);
    return std::unique_ptr<Result>(new StringResult("User successfully removed."));
}

const size_t Controller::ONE_WORD = 1;
const size_t Controller::TWO_WORDS = 2;
const size_t Controller::THREE_WORDS = 3;
const size_t Controller::FOUR_WORDS = 4;