#include "BookServiceImpl.h"
#include "Execute.cpp"

BookServiceImpl::BookServiceImpl(std::unique_ptr<BookRepository> bookRepository)
    : bookRepository{std::move(bookRepository)} {}

void BookServiceImpl::openFile(const std::string &fileName)
{
    execute<void>([this, fileName]() {
        this->bookRepository->setSource(fileName);
        this->bookRepository->fetch();
    });
}
void BookServiceImpl::closeFile()
{
    execute<void>([this]() {
        this->bookRepository->removeSource();
    });
}
void BookServiceImpl::saveFile() const
{
    execute<void>([this]() {
        this->bookRepository->saveChanges();
    });
}
void BookServiceImpl::saveFileAs(const std::string &newFileName)
{
    execute<void>([this, newFileName]() {
        this->bookRepository->removeSource();
        this->bookRepository->setSource(newFileName);
        this->bookRepository->saveChanges();
    });
}
const std::vector<Book> BookServiceImpl::getAllBooks() const
{
    return execute<const std::vector<Book>>([this]() {
        return this->bookRepository->getAllBooks();
    });
}
const std::optional<Book> BookServiceImpl::getBookInfo(const std::string &ISBN) const
{
    return execute<const std::optional<Book>>([this, ISBN]() {
        return this->bookRepository->getBookByISBN(ISBN);
    });
}
const std::vector<Book> BookServiceImpl::findBooksBy(
    const std::string &option, const std::string &optionString) const
{
    return execute<std::vector<Book>>([this, option, optionString]() {
        Filter filter = getFilterFromOption(option);
        std::vector<Book> books = this->bookRepository->getAllBooks();
        std::vector<Book> resList;
        for (const Book &book : books)
        {
            if (filter(book, optionString))
            {
                resList.push_back(book);
            }
        }
        return resList;
    });
}
const std::vector<Book> BookServiceImpl::sortBooksBy(
    const std::string &option, const std::string &order)
{
    return execute<std::vector<Book>>([this, option, order]() {
        Comparator comparator = getComparatorFromOption(option);
        bool asc = getOrderFromString(order);

        std::vector<Book> booksNewOrder(this->bookRepository->getAllBooks());
        for (size_t i = 0; i < booksNewOrder.size(); i++)
        {
            for (size_t j = 0; j < booksNewOrder.size() - i - 1; j++)
            {
                if (comparator(booksNewOrder[j], booksNewOrder[j + 1]) == asc)
                {
                    std::swap(booksNewOrder[j], booksNewOrder[j + 1]);
                }
            }
        }
        return booksNewOrder;
    });
}

const std::vector<Book> BookServiceImpl::sortBooksBy(const std::string &option)
{
    return sortBooksBy(option, "asc");
}
void BookServiceImpl::addBook(const std::string &ISBN, const std::string &csvProperties)
{
    execute<void>(
        [this, ISBN, csvProperties] {
            this->bookRepository->addBook(ISBN, csvProperties);
        },
        "Book");
}
void BookServiceImpl::removeBook(const std::string &ISBN)
{
    execute<void>(
        [this, ISBN] {
            this->bookRepository->removeBook(ISBN);
        },
        "Book");
}

BookServiceImpl::Filter BookServiceImpl::getFilterFromOption(const std::string &option)
{
    OptionToFilterMap::const_iterator mapEntry = optionToFilterMap.find(option);
    if (mapEntry == optionToFilterMap.end())
    {
        throw InvalidParamException(std::string("Option"));
    }
    return mapEntry->second;
}

BookServiceImpl::Comparator BookServiceImpl::getComparatorFromOption(
    const std::string &option)
{
    OptionToComparatorMap::const_iterator mapEntry = optionToComparatorMap.find(option);
    if (mapEntry == optionToComparatorMap.end())
    {
        throw InvalidParamException(std::string("Option"));
    }
    return mapEntry->second;
}

bool BookServiceImpl::getOrderFromString(const std::string &order)
{
    if (order == "asc")
    {
        return true;
    }
    else if (order == "desc")
    {
        return false;
    }
    else
    {
        throw InvalidParamException(std::string("Order"));
    }
}

const BookServiceImpl::OptionToFilterMap BookServiceImpl::optionToFilterMap = {
    {"title", [](const Book &book,
                 const std::string &optionString) { return optionString == book.getTitle(); }},
    {"author", [](const Book &book,
                  const std::string &optionString) { return optionString == book.getAuthor(); }},
    {"tag", [](const Book &book,
               const std::string &optionString) {
         for (const std::string &tag : book.getTags())
         {
             if (tag == optionString)
             {
                 return true;
             }
         }
         return false;
     }},
};

const BookServiceImpl::OptionToComparatorMap BookServiceImpl::optionToComparatorMap = {
    {"title", [](const Book &book1,
                 const Book &book2) { return book1.getTitle().compare(book2.getTitle()) > 0; }},
    {"author", [](const Book &book1,
                  const Book &book2) { return book1.getAuthor().compare(book2.getAuthor()) > 0; }},
    {"year", [](const Book &book1,
                const Book &book2) { return book1.getYear() > book2.getYear(); }},
    {"rating", [](const Book &book1,
                  const Book &book2) { return book1.getRating() > book2.getRating(); }},
};
