#include "TestObject.h"

TestObject::TestObject(int newId, float newValue, std::string startingName)
{
    name = startingName;
    id = newId;
    value = newValue;
}
void TestObject::setName(std::string newName)
{
    name = newName;
}
std::string TestObject::getName()
{
    return name;
}

void TestObject::setID(int newId)
{
    id = newId;
}
int TestObject::getID()
{
    return id;
}
void TestObject::setValue(float newValue)
{
    value = newValue;
}
float TestObject::getValue()
{
    return value;
}

void TestObject::printValues()
{
    std::cout << "Id: " << id << ", value: " << value << ", name: " << name << std::endl;
}