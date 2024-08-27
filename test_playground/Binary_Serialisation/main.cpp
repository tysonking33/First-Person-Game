#include "TestObject.h"
#include "Serialize.h"
int main()
{
    TestObject object1(1, 2.5f, "Beans");
    Serialize *serializer = new Serialize();
    object1.printValues();
    
    serializer->saveToFile(object1, "data.bin");

    TestObject object2;
    serializer->loadFromFile(object2, "data.bin");
    object2.printValues();

    return 0;
}