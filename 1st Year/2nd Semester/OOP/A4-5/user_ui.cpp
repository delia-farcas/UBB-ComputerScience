#include "user_ui.h"
#include <iostream>
#include <limits>

UserUI::UserUI(UserService& service) : service(service) {}

void UserUI::run() {
    bool running = true;

    while (running) {
        displayMenu();
        int choice = readIntegerInput("Enter your choice: ");

        switch (choice) {
        case 1:
            handleViewDogs();
            break;
        case 2:
            handleFilterDogs();
            break;
        case 3:
            handleViewAdoptionList();
            break;
        case 4:
            running = false;
            std::cout << "Exiting user mode...\n";
            break;
        default:
            std::cout << "Invalid choice. Please try again.\n";
            break;
        }
    }
}

void UserUI::displayMenu() {
    std::cout << "\n=== Dog Adoption ===\n";
    std::cout << "1. Browse dogs one by one\n";
    std::cout << "2. Filter dogs by breed and age\n";
    std::cout << "3. View adoption list\n";
    std::cout << "4. Exit\n";
}

void UserUI::handleViewDogs() {
    if (service.getDogCount() == 0) {
        std::cout << "No dogs available.\n";
        return;
    }

    bool browsing = true;
    while (browsing) {
        const Dog* currentDog = service.getCurrentDog();
        if (!currentDog) {
            std::cout << "No dogs available.\n";
            return;
        }

        displayDog(currentDog);

        std::cout << "\nOptions:\n";
        std::cout << "1. Adopt this dog\n";
        std::cout << "2. Next dog\n";
        std::cout << "3. Return to main menu\n";

        int choice = readIntegerInput("Enter your choice: ");

        switch (choice) {
        case 1:
            if (service.adoptCurrentDog()) {
                std::cout << "Dog adopted successfully!\n";
            } else {
                std::cout << "You've already adopted this dog.\n";
            }
            break;
        case 2:
            service.nextDog();
            break;
        case 3:
            browsing = false;
            break;
        default:
            std::cout << "Invalid choice. Please try again.\n";
            break;
        }
    }
}

void UserUI::handleFilterDogs() {
    std::cout << "\nFilter Dogs\n";
    
    std::string breed = readStringInput("Enter breed (leave empty for all breeds): ");
    int maxAge = readIntegerInput("Enter maximum age: ");
    
    service.filterDogs(breed, maxAge);
    
    if (service.getDogCount() == 0) {
        std::cout << "No dogs match your criteria.\n";
        service.clearFilter();
    } else {
        std::cout << "Filter applied. " << service.getDogCount() << " dogs found.\n";
        handleViewDogs();
        service.clearFilter();
    }
}

void UserUI::handleViewAdoptionList() {
    const DynamicVector<Dog>& adoptedDogs = service.getAdoptionList();
    
    if (adoptedDogs.size() == 0) {
        std::cout << "Your adoption list is empty.\n";
        return;
    }
    
    std::cout << "\nYour Adoption List-------------------------------------------------------------------\n";
    for (int i = 0; i < adoptedDogs.size(); i++) {
        const Dog& dog = adoptedDogs[i];
        std::cout << "Dog #" << (i + 1) << ":\n";
        //std::cout << "  ID: " << dog.getId() << "\n";
        std::cout << "  Name: " << dog.getName() << "\n";
        std::cout << "  Breed: " << dog.getBreed() << "\n";
        std::cout << "  Age: " << dog.getAge() << " years\n";
        std::cout << "  Photograph: " << dog.getPhotograph() << "\n\n";
    }
    std::cout << "-------------------------------------------------------------------------------------\n";
}

void UserUI::displayDog(const Dog* dog) {
    std::cout << "\nDog Details:\n";
    std::cout << "Name: " << dog->getName() << "\n";
    std::cout << "Breed: " << dog->getBreed() << "\n";
    std::cout << "Age: " << dog->getAge() << " years\n";
    std::cout << "Photograph: " << dog->getPhotograph() << "\n";
}

int UserUI::readIntegerInput(const std::string& prompt) {
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

std::string UserUI::readStringInput(const std::string& prompt) {
    std::string value;

    std::cout << prompt;
    std::getline(std::cin, value);

    return value;
}

