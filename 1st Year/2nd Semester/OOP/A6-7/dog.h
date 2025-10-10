#pragma once
#include "exceptions.h"
#include <string>
#include <iostream>
using namespace std;

class Dog {
private:
    int id;
    string name;
    string breed;
    int age;
    string photograph;

public:
    // Constructor
    Dog(int id = 0, const string& name = "", const string& breed = "",
        int age = 0, const string& photograph = "");

    // Getters
    int getId() const;
    string getName() const;
    string getBreed() const;
    int getAge() const;
    string getPhotograph() const;

    // Setters
    void setId(int newId);
    void setName(const string& newName);
    void setBreed(const string& newBreed);
    void setAge(int newAge);
    void setPhotograph(const string& newPhotograph);

    // Friend operators for file I/O
    friend ostream& operator<<(ostream& os, const Dog& dog);
    friend istream& operator>>(istream& is, Dog& dog);
};


class DogValidator {
public:
    static void validateDog(const Dog& dog);
};



// Insertion operator for Dog
ostream& operator<<(ostream& os, const Dog& dog);

// Extraction operator for Dog
istream& operator>>(istream& is, Dog& dog);
