#include "admin_ui.h"


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
            cout << "Exiting administrator mode..\n";
            break;
        default:
            cout << "Invalid choice. Please try again.\n";
            break;
        }
    }
}

void UI::displayMenu() {
    cout << "\n=== Dog Shelter Management ===\n";
    cout << "1. Display all dogs\n";
    cout << "2. Add a new dog\n";
    cout << "3. Remove a dog\n";
    cout << "4. Update dog information\n";
    cout << "5. Exit\n";
}

void UI::handleAddDog() {
    cout << "\nAdd a New Dog\n";

    string name = readStringInput("Enter dog name: ");
    string breed = readStringInput("Enter dog breed: ");
    int age = readIntegerInput("Enter dog age: ");
    string photograph = readStringInput("Enter photograph URL: ");

    try{
        service.addDog(name, breed, age, photograph);
        cout << "Dog added succesfully!<3\n";
    }
    catch (const ValidationException& e) {
        cerr << e.what() << endl;
    }
    catch (const RepositoryException& e) {
        cerr << e.what() << endl;
    }

}

void UI::handleRemoveDog() {
    cout << "\nRemove a Dog\n";

    int id = readIntegerInput("Enter dog ID to remove: ");

    try {
        service.removeDog(id);
        cout << "Dog removed :(\n";
    }
    catch (const RepositoryException& e) {
        cerr << e.what() << endl;
    }
   
}

void UI::handleUpdateDog() {
    cout << "\nUpdate Dog Information\n";

    int id = readIntegerInput("Enter dog ID to update: ");
    string name = readStringInput("Enter new name: ");
    string breed = readStringInput("Enter new breed: ");
    int age = readIntegerInput("Enter new age: ");
    string photograph = readStringInput("Enter new photograph URL: ");

    try {
        service.updateDog(id, name, breed, age, photograph);
        cout << "Dog updated successfully.\n";
    }
    catch (const RepositoryException& e) {
        cerr << e.what() << endl;
    }
}

void UI::handleDisplayAllDogs() {
    vector<Dog> allDogs = service.getAllDogs();

    if (allDogs.empty()) {
        cout << "No dogs in the shelter.\n";
        return;
    }

    cout << "\nAll Dogs------------------------------------------------------------------------------\n";
    int i = 1;
    for (Dog dog : allDogs) {
        cout << "Dog #" << i << ":\n";
        cout << "  ID: " << dog.getId() << "\n";
        cout << "  Name: " << dog.getName() << "\n";
        cout << "  Breed: " << dog.getBreed() << "\n";
        cout << "  Age: " << dog.getAge() << " years\n";
        cout << "  Photograph: " << dog.getPhotograph() << "\n\n";
        i++;
    }
    cout << "-------------------------------------------------------------------------------------\n";
}

int UI::readIntegerInput(const string& prompt) {
    int value;
    bool validInput = false;

    while (!validInput) {
        cout << prompt;
        cin >> value;

        if (cin.fail()) {
            cin.clear();
            cin.ignore(numeric_limits<streamsize>::max(), '\n');
            cout << "Invalid input. Please enter a number.\n";
        }
        else {
            validInput = true;
            cin.ignore(numeric_limits<streamsize>::max(), '\n');
        }
    }

    return value;
}

string UI::readStringInput(const string& prompt) {
    string value;

    cout << prompt;
    getline(cin, value);

    return value;
}