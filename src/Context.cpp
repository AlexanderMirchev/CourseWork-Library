#include "Context.h"

// throw exceptions depending on state

void Context::open(const std::string& filename) {
    if(this->bookSerializer.has_value) {
        // throw 
    }
    this->bookSerializer = EntitySerializer<Book>(filename);
    this->bookCache = BookCacheRepository(this->bookSerializer.value);
}
void Context::close() {
    if(!this->bookSerializer.has_value) {
        // throw
    }
    this->bookSerializer = std::nullopt;

}
void Context::save() const {
    if(!this->bookSerializer.has_value) {
        // throw
    }
    this->bookSerializer.value
        .writeAllEntities(this->bookCache.getAllBooks());
}
void Context::saveas(const std::string& newFileName) {
    if(!this->bookSerializer.has_value) {
        // throw
    }
    this->bookSerializer = EntitySerializer<Book>(newFileName);;
    this->bookSerializer.value
        .writeAllEntities(this->bookCache.getAllBooks());    
}