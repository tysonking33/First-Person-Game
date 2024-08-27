#ifndef TESTOBJECT_H
#define TESTOBJECT_H

#include <iostream>
#include <string.h>

class TestObject
{
public:
    TestObject() : id(0), value(0.0f), name("") {}  // Default constructor

TestObject(int newId, float newValue, std::string startingName);
    void setName(std::string newName);
    std::string getName();
    void setID(int newId);
    int getID();
    void setValue(float newValue);
    float getValue();
    void printValues();

private:
        int id;
        float value;
        std::string name;

};

#endif