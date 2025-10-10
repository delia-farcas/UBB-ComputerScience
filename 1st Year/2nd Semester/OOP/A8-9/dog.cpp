#include "dog.h"
#include <sstream>

Dog::Dog(int id, const string& name, const string& breed,
    int age, const string& photograph)
    : id(id), name(name), breed(breed), age(age), photograph(photograph) {
}

int Dog::getId() const { return id; }
string Dog::getName() const { return name; }
string Dog::getBreed() const { return breed; }
int Dog::getAge() const { return age; }
string Dog::getPhotograph() const { return photograph; }

void Dog::setId(int newId) { id = newId; }
void Dog::setName(const string& newName) { name = newName; }
void Dog::setBreed(const string& newBreed) { breed = newBreed; }
void Dog::setAge(int newAge) { age = newAge; }
void Dog::setPhotograph(const string& newPhotograph) { photograph = newPhotograph; }

string Dog::to_str() {
    return this->getName() + ", age: " + to_string(this->getAge()) + ", photograph: " + this->getPhotograph();
}
ostream& operator<<(ostream& os, const Dog& dog) {
    os << dog.id << "|" << dog.name << "|" << dog.breed << "|"
        << dog.age << "|" << dog.photograph;
    return os;
}

istream& operator>>(istream& is, Dog& dog) {
    string line;
    if (getline(is, line)) {
        stringstream ss(line);
        string token;

        getline(ss, token, '|');
        dog.id = stoi(token);

        getline(ss, dog.name, '|');

        getline(ss, dog.breed, '|');

        getline(ss, token, '|');
        dog.age = stoi(token);

        getline(ss, dog.photograph);
    }
    return is;
}

void DogValidator::validateDog(const Dog& dog) {
    if (dog.getName().empty()) {
        throw ValidationException("The dog should have a name.");
    }
    if (dog.getAge() < 0) {
        throw ValidationException("How can a dog have an age less than 0 years?:)");
    }

}