#ifndef ENTITYSERIALIZER_H
#define ENTITYSERIALIZER_H

#include <fstream>
#include <string>
#include <vector>

#include "../entities/Serializable.h"
#include "../repositories/RepositoryExceptions.cpp"

/**
 * Template class for serialization/deserialization of objects from files
*/
template <class T>
class EntitySerializer
{

private:
    std::string filename;

public:
    /**
     * Constructor with name of the file to be worked with
     * 
     * Assertion for template class to be of type Serializable
    */
    EntitySerializer(const std::string &filename)
    {
        static_assert(std::is_base_of<Serializable, T>::value, "Template must extend Serializable");
        this->filename = filename;
    }

    /**
     * Returns a vector of entities read from file
     * 
     * Throws BadFormatException if the format of the file does not match the entity
    */
    const std::vector<T> readAllEntities() const
    {
        std::ifstream file;
        file.open(this->filename);

        std::vector<T> resList;
        if (file.is_open())
        {
            std::string line;
            while (std::getline(file, line))
            {

                try
                {
                    T entity;
                    entity.stringToObject(line);
                    resList.push_back(entity);
                }
                catch (const std::invalid_argument &e)
                {
                    throw BadFormatException();
                }
            }
        }

        file.close();
        return resList;
    }

    /**
     * Saves all entities to the given file 
     * (erases everything in file written before that)
    */
    void writeAllEntities(const std::vector<T> &entities) const
    {
        std::ofstream file;
        file.open(this->filename, std::ios::trunc);

        for (const T &obj : entities)
        {
            file << obj.objToString() << std::endl;
        }

        file.close();
    }
};
#endif
