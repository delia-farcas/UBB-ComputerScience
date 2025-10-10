#pragma once
#include "service1.h"

class UI {
private:
    DogService& service;

    void displayMenu();
    void handleAddDog();
    void handleRemoveDog();
    void handleUpdateDog();
    void handleDisplayAllDogs();
    
    int readIntegerInput(const std::string& prompt);
    std::string readStringInput(const std::string& prompt);

public:
    UI(DogService& service);
    void run();
};