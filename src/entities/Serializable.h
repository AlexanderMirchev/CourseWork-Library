#ifndef _SERIALIZABLE_HH
#define _SERIALIZABLE_HH

#include <functional>
#include <string>
#include <vector>

/*  
    An abstract class for entities that can be converted to string 
    and can be constructed from a string.
*/

class Serializable
{
public:
    /*
        Object must contain a function that converts it to string
    */
    virtual const std::string objToString() const = 0;

    /*
        Object must contain a function that creates object from string
    */
    virtual void stringToObject(const std::string &) = 0;

protected:
    /*
        Helper function that converts a CSV string to vector of strings
    */
    const std::vector<std::string> separateCSVs(const std::string &string);

private:
    /*
        Mapping function for each character in a string
    */
    void map(const std::string &string, const std::function<void(const char &)> &func);
};
#endif
