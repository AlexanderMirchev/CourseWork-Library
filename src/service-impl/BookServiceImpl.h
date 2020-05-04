#ifndef BOOKSERVICEIMPL_H
#define BOOKSERVICEIMPL_H

#include <memory>
#include <map>

#include "../services/BookService.h"
#include "../repositories/BookRepository.h"

class BookServiceImpl : public BookService
{

private:
    std::unique_ptr<BookRepository> bookRepository;

public:
    void openFile(const std::string &fileName) override;

    void closeFile() override;

    void saveFile() const override;

    void saveFileAs(const std::string &newFileName) override;

    const std::vector<Book> &getAllBooks() const override;

    const std::optional<Book> getBookInfo(const std::string &ISBN) const override;

    const std::vector<Book> findBooksBy(
        const std::string &option, const std::string &optionString) const override;

    const std::vector<Book> sortBooksBy(const std::string &option, const std::string &ascdesc) override;

    const std::vector<Book> sortBooksBy(const std::string &option) override;

    BookServiceImpl(std::unique_ptr<BookRepository> bookRepository);

private:
    using Filter = std::function<bool(const Book &, const std::string &)>;
    using OptionToFilterMap = std::map<std::string, Filter>;

    using Comparator = std::function<bool(const Book &, const Book &)>;
    using OptionToComparatorMap = std::map<std::string, Comparator>;
    /*
        Map keeping pairs of type <option, filter>
    */

    static Filter getFilterFromOption(const std::string &);
    static Comparator getComparatorFromOption(const std::string &);
    static bool getOrderFromString(const std::string &);

    static const OptionToComparatorMap optionToComparatorMap;
    static const OptionToFilterMap optionToFilterMap;
};
#endif
