#pragma once
#include "service.h"
#include <iostream>
#include <limits>
using namespace std;

class UI {
private:
    DogService& service;

    void displayMenu();
    void handleAddDog();
    void handleRemoveDog();
    void handleUpdateDog();
    void handleDisplayAllDogs();
    
    int readIntegerInput(const string& prompt);
    string readStringInput(const string& prompt);

public:
    UI(DogService& service);
    void run();
};