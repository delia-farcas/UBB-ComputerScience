#pragma once
#include "user_service.h"

/**
 * @brief User interface for dog adoption functionality.
 * 
 * Provides methods for displaying dogs, adopting, and viewing adoption list.
 */
class UserUI {
private:
    UserService& service;

    void displayMenu();
    void handleViewDogs();
    void handleFilterDogs();
    void handleViewAdoptionList();
    void displayDog(const Dog* dog);
    
    int readIntegerInput(const std::string& prompt);
    std::string readStringInput(const std::string& prompt);

public:
    /**
     * @brief Constructs a UserUI with a service reference.
     * @param service Reference to the UserService to use.
     */
    UserUI(UserService& service);
    
    /**
     * @brief Runs the user interface main loop.
     * @post Displays menu and handles user input until exit.
     */
    void run();
};

