#include "Serialize.h"

void Serialize::serialize(TestObject &object, std::ostream &os) {
    int id = object.getID();
    float value = object.getValue();
    os.write(reinterpret_cast<const char *>(&id), sizeof(id));
    os.write(reinterpret_cast<const char *>(&value), sizeof(value));
    
    size_t nameLength = object.getName().size();
    os.write(reinterpret_cast<const char *>(&nameLength), sizeof(nameLength));
    os.write(object.getName().data(), nameLength);
}

void Serialize::deserialize(TestObject &object, std::istream &is) {
    int id;
    float value;
    size_t nameLength;

    is.read(reinterpret_cast<char *>(&id), sizeof(id));
    is.read(reinterpret_cast<char *>(&value), sizeof(value));
    is.read(reinterpret_cast<char *>(&nameLength), sizeof(nameLength));

    std::string name;
    name.resize(nameLength);
    is.read(&name[0], nameLength);

    object.setID(id);
    object.setValue(value);
    object.setName(name);
}

void Serialize::saveToFile(TestObject &object, const std::string &filename) {
    std::ofstream ofs(filename, std::ios::binary);
    if (ofs.is_open()) {
        serialize(object, ofs);
        ofs.close();
    } else {
        std::cerr << "Failed to open file for writing: " << filename << std::endl;
    }
}

void Serialize::loadFromFile(TestObject &object, const std::string &filename) {
    std::ifstream ifs(filename, std::ios::binary);
    if (ifs.is_open()) {
        deserialize(object, ifs);
        ifs.close();
    } else {
        std::cerr << "Failed to open file for reading: " << filename << std::endl;
    }
}
