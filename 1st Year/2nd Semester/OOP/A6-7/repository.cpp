#include "repository.h"
#include <algorithm>
#include <stdexcept>

Repository::Repository(const string& filename) : filename(filename) {
    loadFromFile();
}

void Repository::loadFromFile() {
    ifstream file(filename);

    if (!file.is_open()) {
        return;
    }

    dogs.clear();

    Dog dog;
    while (file >> dog) {
        dogs.push_back(dog);
    }

    file.close();
}

void Repository::saveToFile() const {
    ofstream file(filename);

    if (!file.is_open()) {
        throw runtime_error("Could not open file for writing: " + filename);
    }

    for (const Dog& dog : dogs) {
        file << dog << endl;
    }

    file.close();
}

void Repository::addDog(const Dog& dog) {
    DogValidator::validateDog(dog);
    if (exists_for_add(dog.getName(), dog.getBreed(), dog.getAge())) {
        throw RepositoryException("Dog already in the shelter.");
    }

    dogs.push_back(dog);
    saveToFile();
}

void Repository::removeDog(int id) {
    auto it = find_if(dogs.begin(), dogs.end(),
        [id](const Dog& dog) { return dog.getId() == id; });

    if (it == dogs.end()) {
        throw RepositoryException("Dog not in shelter.");
    }

    dogs.erase(it);
    saveToFile();
}

void Repository::updateDog(int id, const Dog& newDogData) {
    Dog* dog = findDogById(id);
    if (!dog) {
        throw RepositoryException("Dog not in shelter.");
    }

    *dog = newDogData;
    saveToFile();
}

const vector<Dog>& Repository::getAllDogs() const {
    return dogs;
}

Dog* Repository::findDogById(int id) {
    for (Dog& dog : dogs) {
        if (dog.getId() == id)
            return &dog;
    }
    return nullptr;
}

const Dog* Repository::findDogById(int id) const {
    for (const Dog& dog : dogs) {
        if (dog.getId() == id)
            return &dog;
    }
    return nullptr;
}

const Dog* Repository::findDogByData(string name, string breed, int age) const {
    for (const Dog& dog : dogs) {
        if (dog.getName() == name && dog.getBreed() == breed && dog.getAge() == age)
            return &dog;
    }
    return nullptr;
}

bool Repository::exists_for_add(string name, string breed, int age) const {
    return findDogByData(name, breed, age) != nullptr;
}

bool Repository::exists(int id) const {
    return findDogById(id) != nullptr;
}

int Repository::getSize() const {
    return dogs.size();
}
