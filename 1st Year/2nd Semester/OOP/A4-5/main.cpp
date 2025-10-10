#include "admin_ui.h"
#include "user_ui.h"
#include "service1.h"
#include "repository1.h"
#include "tests.h"
#include "tests_user.h"
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

int readIntegerInput(const std::string& prompt) {
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

int main() {
    {
        Repository repo;
        DogService service(repo);
        service.generateSampleDogs();
        UI adminUI(service);
        UserService userService(repo);
        UserUI userUI(userService);

        cout << "From shelter to family, from stray to adored\n";
        cout << "love is the magic no store can afford\n";
        //runAllTests();
        //runUserTests();
        
       while (true) {
            principal_menu();
            int choice = readIntegerInput("Enter your choice: ");

            switch (choice) {
            case 1: {
                adminUI.run();
                break;
            }
            case 2: {
                userUI.run();
                break;
            }
            case 0: {
                cout << "Goodbye...\n";
                return 0;
            }
            default:
                cout << "Invalid choice. Please try again.\n";
                break;
            }
        
        
        }

        
    }

    _CrtDumpMemoryLeaks();
    return 0;
}

