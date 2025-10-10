#pragma once
#include "Dog.h"
#include <vector>
#include <string>
using namespace std;

class AdoptionList {
public:
    virtual void save(const Dog& dog) = 0;
    virtual vector<Dog> getElements() = 0;
    virtual void displayList() const = 0;
    virtual ~AdoptionList() = default;
};