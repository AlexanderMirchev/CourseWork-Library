#ifndef ENTITYSERIALIZER_H
#define ENTITYSERIALIZER_H

#include <fstream>
#include <string>
#include <vector>

#include "../entities/Serializable.h"

/*
    Template class for serializing/deserializing objects from files
*/
template<class T>
class EntitySerializer {

private:
    std::string fileName;
public:
    EntitySerializer(const std::string& string) {
        static_assert(std::is_base_of<Serializable, T>::value, "Template must extend Serializable");
        this->fileName = string;
    }
    /*
        Returns a vector of entities read from file

        throws BadFormatException if the format of the file does not match the entity
    */
    const std::vector<T> readAllEntities() const {
        std::ifstream file;
        file.open(this->fileName);

        std::vector<T> resList;
        if(file.is_open()) {
            std::string line;
            while (std::getline(file, line)) {
                T entity;
                entity.stringToObject(line);
                resList.push_back(entity);
            }
        }

        file.close();
        return resList;
    }

    /*
        Saves all entities to the given file
        (erases everything in file written before that)
    */
    void writeAllEntities(const std::vector<T>& entities) const {
        std::ofstream file;
        file.open(this->fileName, std::ios::trunc);

        for(const T& obj : entities) {
            file << obj.objToString() << std::endl;
        }

        file.close();
    }
};
#endif
