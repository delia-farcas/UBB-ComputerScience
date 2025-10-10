#include "admin_ui.h"
#include <iostream>
#include <limits>

UI::UI(DogService& service) : service(service) {}

void UI::run() {
    bool running = true;

    while (running) {
        displayMenu();
        int choice = readIntegerInput("Enter your choice: ");

        switch (choice) {
        case 1:
            handleDisplayAllDogs();
            break;
        case 2:
            handleAddDog();
            break;
        case 3:
            handleRemoveDog();
            break;
        case 4:
            handleUpdateDog();
            break;
        case 5:
            running = false;
            std::cout << "Exiting administrator mode..\n";
            break;
        default:
            std::cout << "Invalid choice. Please try again.\n";
            break;
        }
    }
}

void UI::displayMenu() {
    std::cout << "\n=== Dog Shelter Management ===\n";
    std::cout << "1. Display all dogs\n";
    std::cout << "2. Add a new dog\n";
    std::cout << "3. Remove a dog\n";
    std::cout << "4. Update dog information\n";
    std::cout << "5. Exit\n";
}

void UI::handleAddDog() {
    std::cout << "\nAdd a New Dog\n";

    std::string name = readStringInput("Enter dog name: ");
    std::string breed = readStringInput("Enter dog breed: ");
    int age = readIntegerInput("Enter dog age: ");
    std::string photograph = readStringInput("Enter photograph URL: ");

    bool success = service.addDog(name, breed, age, photograph);

    if (success) {
        std::cout << "Dog added successfully!\n";
    }
    else {
        std::cout << "Error: Dog with this ID already exists!\n";
    }
}

void UI::handleRemoveDog() {
    std::cout << "\nRemove a Dog\n";

    int id = readIntegerInput("Enter dog ID to remove: ");

    bool success = service.removeDog(id);

    if (success) {
        std::cout << "Dog removed successfully!\n";
    }
    else {
        std::cout << "Error: Dog with ID " << id << " does not exist!\n";
    }
}

void UI::handleUpdateDog() {
    std::cout << "\nUpdate Dog Information\n";

    int id = readIntegerInput("Enter dog ID to update: ");
    std::string name = readStringInput("Enter new name: ");
    std::string breed = readStringInput("Enter new breed: ");
    int age = readIntegerInput("Enter new age: ");
    std::string photograph = readStringInput("Enter new photograph URL: ");

    bool success = service.updateDog(id, name, breed, age, photograph);

    if (success) {
        std::cout << "Dog information updated successfully!\n";
    }
    else {
        std::cout << "Error: Dog with ID " << id << " does not exist!\n";
    }
}

void UI::handleDisplayAllDogs() {
    DynamicVector<Dog> allDogs = service.getAllDogs();

    if (allDogs.isEmpty()) {
        std::cout << "No dogs in the shelter.\n";
        return;
    }

    std::cout << "\nAll Dogs------------------------------------------------------------------------------\n";
    for (int i = 0; i < allDogs.size(); i++) {
        Dog dog = allDogs[i];
        std::cout << "Dog #" << (i + 1) << ":\n";
        std::cout << "  ID: " << dog.getId() << "\n";
        std::cout << "  Name: " << dog.getName() << "\n";
        std::cout << "  Breed: " << dog.getBreed() << "\n";
        std::cout << "  Age: " << dog.getAge() << " years\n";
        std::cout << "  Photograph: " << dog.getPhotograph() << "\n\n";
    }
    std::cout << "-------------------------------------------------------------------------------------\n";
}

int UI::readIntegerInput(const std::string& prompt) {
    int value;
    bool validInput = false;

    while (!validInput) {
        std::cout << prompt;
        std::cin >> value;

        if (std::cin.fail()) {
            std::cin.clear();
            std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
            std::cout << "Invalid input. Please enter a number.\n";
        }
        else {
            validInput = true;
            std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
        }
    }

    return value;
}

std::string UI::readStringInput(const std::string& prompt) {
    std::string value;

    std::cout << prompt;
    std::getline(std::cin, value);

    return value;
}