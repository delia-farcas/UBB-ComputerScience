#include "admin_ui.h"
#include "user_ui.h"
#include <iostream>
#include <crtdbg.h> 
using namespace std;

void principal_menu() {
    cout << "\n==== Keep calm and adopt a pet ====\n";
    cout << "Choose mode:\n";
    cout << "1. Admin\n";
    cout << "2. User\n";
    cout << "0. Exit\n";
}

int readIntegerInput(const string& prompt) {
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

int main() {
    {
        Repository repo("dogs.txt");
        DogService service(repo);

        if (repo.getSize() == 0) {
            service.generateSampleDogs();
        }

        std::unique_ptr<AdoptionList> adoptionList;
        bool ok = true;
        while (true) {
            cout << "Enter adoption list type: \n";
            cout << "1. CSV\n";
            cout << "2. HTML\n";
            int option = readIntegerInput("Enter option: ");

            if (option == 1) {
                adoptionList = std::make_unique<AdoptionListCSV>("adoption_list.csv");
                cout << "Adoption list in CSV file.\n\n";
                break;
            }
            else if (option == 2) {
                adoptionList = std::make_unique<AdoptionListHTML>("adoption_list.html");
                cout << "Adoption list in HTML file.\n\n";
                break;
            }
            else {
                cerr << "Invalid option.\n";
            }
        }

        UI adminUI(service);
        UserService userService(repo, *adoptionList);  // Pass reference
        UserUI userUI(userService);

        cout << "From shelter to family, from stray to adored\n";
        cout << "love is the magic no store can afford\n";

        while (true) {
            principal_menu();
            int choice = readIntegerInput("Enter your choice: ");

            switch (choice) {
            case 1:
                adminUI.run();
                break;
            case 2:
                userUI.run();
                break;
            case 0:
                cout << "Goodbye...\n";
                return 0;
            default:
                cout << "Invalid choice. Please try again.\n";
                break;
            }
        }
    }

    _CrtDumpMemoryLeaks();
    return 0;
}

