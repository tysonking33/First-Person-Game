#ifndef BINSER_H
#define BINSER_H

#include <fstream>
#include "TestObject.h"

class Serialize{
public:
    void serialize(TestObject &object, std::ostream &os);
    void deserialize(TestObject &object, std::istream &is);

    void saveToFile(TestObject &object,const std::string &filename);
    void loadFromFile(TestObject &object, const std::string &filename);
    
    
};


#endif