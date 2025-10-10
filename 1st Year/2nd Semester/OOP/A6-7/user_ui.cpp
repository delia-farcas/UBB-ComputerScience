#include "user_ui.h"


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
            handleDisplayAdoptionList();
            break;
        case 5:
            running = false;
            cout << "Exiting user mode...\n";
            break;
        default:
            cout << "Invalid choice. Please try again.\n";
            break;
        }
    }
}

void UserUI::displayMenu() {
    cout << "\n=== Dog Adoption ===\n";
    cout << "1. Browse dogs one by one\n";
    cout << "2. Filter dogs by breed and age\n";
    cout << "3. View adoption list in console\n";
    cout << "4. Display adoption list in external application\n";
    cout << "5. Exit\n";
}

void UserUI::handleViewDogs() {
    if (service.getDogCount() == 0) {
        cout << "No dogs available.\n";
        return;
    }

    bool browsing = true;
    while (browsing) {
        const Dog* currentDog = service.getCurrentDog();
        if (!currentDog) {
            cout << "No dogs available.\n";
            return;
        }

        displayDog(currentDog);

        cout << "\nOptions:\n";
        cout << "1. Adopt this dog\n";
        cout << "2. Next dog\n";
        cout << "3. Return to main menu\n";

        int choice = readIntegerInput("Enter your choice: ");

        switch (choice) {
        case 1:
            try {
                service.adoptCurrentDog();
                cout << "Dog adopted successfully!\n";
            }
            catch (const RepositoryException& e) {
                cerr << e.what() << endl;
            }
            break;
        case 2:
            service.nextDog();
            break;
        case 3:
            browsing = false;
            break;
        default:
            cout << "Invalid choice. Please try again.\n";
            break;
        }
    }
}

void UserUI::handleFilterDogs() {
    cout << "\nFilter Dogs\n";

    string breed = readStringInput("Enter breed (leave empty for all breeds): ");
    int maxAge = readIntegerInput("Enter maximum age: ");

    service.filterDogs(breed, maxAge);

    if (service.getDogCount() == 0) {
        cout << "No dogs match your criteria.\n";
        service.clearFilter();
    }
    else {
        cout << "Filter applied. " << service.getDogCount() << " dogs found.\n";
        handleViewDogs();
        service.clearFilter();
    }
}

void UserUI::handleViewAdoptionList() {
    const vector<Dog>& adoptedDogs = service.getAdoptionList();

    if (adoptedDogs.size() == 0) {
        cout << "Your adoption list is empty.\n";
        return;
    }

    cout << "\nYour Adoption List-------------------------------------------------------------------\n";
    int i = 1;
    for (const Dog& dog : adoptedDogs) {
        cout << "Dog #" << i << ":\n";
        //cout << "  ID: " << dog.getId() << "\n";
        cout << "  Name: " << dog.getName() << "\n";
        cout << "  Breed: " << dog.getBreed() << "\n";
        cout << "  Age: " << dog.getAge() << " years\n";
        cout << "  Photograph: " << dog.getPhotograph() << "\n\n";
        i++;
    }
    cout << "-------------------------------------------------------------------------------------\n";
}

void UserUI::handleDisplayAdoptionList() {
    const vector<Dog>& adoptedDogs = service.getAdoptionList();

    if (adoptedDogs.size() == 0) {
        cout << "Your adoption list is empty.\n";
        return;
    }

    try {
        service.displayAdoptionList();
        cout << "Opening adoption list in external application...\n";
    }
    catch (const exception& e) {
        cerr << "Error displaying adoption list: " << e.what() << endl;
    }
}

void UserUI::displayDog(const Dog* dog) {
    cout << "\nDog Details:\n";
    cout << "Name: " << dog->getName() << "\n";
    cout << "Breed: " << dog->getBreed() << "\n";
    cout << "Age: " << dog->getAge() << " years\n";
    cout << "Photograph: " << dog->getPhotograph() << "\n";
}

int UserUI::readIntegerInput(const string& prompt) {
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

string UserUI::readStringInput(const string& prompt) {
    string value;

    cout << prompt;
    getline(cin, value);

    return value;
}
