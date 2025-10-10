#include "dog.h"

// Implement the default constructor
Dog::Dog() : id(0), name(""), breed(""), age(0), photograph("") {
    // Initialize with default values
}

Dog::Dog(int id, std::string name, std::string breed, int age, std::string photograph) {
    this->id = id;
    this->name = name;
    this->breed = breed;
    this->age = age;
    this->photograph = photograph;
}

//getters
int Dog::getId() const {
    return id;
}

std::string Dog::getBreed() const {
    return breed;
}

std::string Dog::getName() const {
    return name;
}

int Dog::getAge() const {
    return age;
}

std::string Dog::getPhotograph() const {
    return photograph;
}

//setters
void Dog::setBreed(const std::string& newBreed) {
    breed = newBreed;
}

void Dog::setName(const std::string& newName) {
    name = newName;
}

void Dog::setAge(int newAge) {
    age = newAge;
}

void Dog::setPhotograph(const std::string& newPhoto) {
    photograph = newPhoto;
}