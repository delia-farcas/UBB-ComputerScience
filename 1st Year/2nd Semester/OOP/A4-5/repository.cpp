#include "repository1.h"

bool Repository::addDog(const Dog& dog) {
    if (exists_for_add(dog.getName(), dog.getBreed(), dog.getAge()))
        return false;
    dogs.add(dog);
    return true;
}

bool Repository::removeDog(int id) {
    for (int i = 0; i < dogs.size(); i++) {
        if (dogs[i].getId() == id) {
            Dog toRemove = dogs[i];
            dogs.remove(toRemove);
            return true;
        }
    }
    return false;
}

bool Repository::updateDog(int id, const Dog& newDogData) {
    Dog* dog = findDogById(id);
    if (!dog) return false;
    *dog = newDogData;
    return true;
}

const DynamicVector<Dog>& Repository::getAllDogs() const {
    return dogs;
}

Dog* Repository::findDogById(int id) {
    for (int i = 0; i < dogs.size(); i++) {
        if (dogs[i].getId() == id)
            return &dogs[i];
    }
    return nullptr;
}

const Dog* Repository::findDogById(int id) const {
    for (int i = 0; i < dogs.size(); i++) {
        if (dogs[i].getId() == id)
            return &dogs[i];
    }
    return nullptr;
}

const Dog* Repository::findDogByData(std::string name, std::string breed, int age) const {
    for (int i = 0; i < dogs.size(); i++) {
        if (dogs[i].getName() == name && dogs[i].getBreed() == breed && dogs[i].getAge() == age)
            return &dogs[i];
    }
    return nullptr;
}

bool Repository::exists_for_add(std::string name, std::string breed, int age) const {
    return findDogByData(name, breed, age) != nullptr;
}

bool Repository::exists(int id) const {
    return findDogById(id) != nullptr;
}

int Repository::getSize() const {
    return dogs.size();
}