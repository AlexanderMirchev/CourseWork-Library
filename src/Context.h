#ifndef _CONTEXT_HH
#define _CONTEXT_HH

#include <optional>

#include "entities/User.h"
#include "repositories/EntitySerializer.h"
#include "repositories/BookCacheRepository.h"
#include "repositories/UserCacheRepository.h"

class Context
{
private:
    EntitySerializer<User> userSerializer;
    std::optional< EntitySerializer<Book> >  bookSerializer;

    UserCacheRepository userCache;
    BookCacheRepository bookCache;

public:
    Context(): userSerializer{EntitySerializer<User>("users.txt")}  {
        userCache = UserCacheRepository(this->userSerializer);    
    }

    void open(const std::string&);
    void close();
    void save() const;
    void saveas(const std::string&); 
};

#endif
