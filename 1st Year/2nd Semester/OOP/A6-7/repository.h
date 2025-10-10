#pragma once
#include <vector>
#include <string>
#include <fstream>
#include "dog.h"

/**
 * @brief Repository class for managing Dog objects with file persistence.
 *
 * Provides CRUD operations for Dog entities using a vector as storage
 * and persists data to a text file.
 */
class Repository {
private:
    vector<Dog> dogs; ///< Internal storage for Dog objects
    string filename;  ///< Path to the file for storing dogs

    /**
     * @brief Loads dogs from the file into memory
     */
    void loadFromFile();

    /**
     * @brief Saves the current dogs in memory to the file
     */
    void saveToFile() const;

public:
    /**
     * @brief Constructor that initializes the repository with a file
     * @param filename The path to the file for storing dogs
     */
    Repository(const string& filename = "dogs.txt");

    // --- Modifiers ---

    /**
     * @brief Adds a new dog to the repository.
     * @param dog The Dog object to add.
     * @return true if dog was added successfully, false if a dog with same data already exists.
     * @post The dogs collection size increases by 1 and file is updated if successful.
     */
    void addDog(const Dog& dog);

    /**
     * @brief Removes a dog from the repository by ID.
     * @param id The ID of the dog to remove.
     * @return true if dog was found and removed, false otherwise.
     * @post The dogs collection size decreases by 1 and file is updated if successful.
     */
    void removeDog(int id);

    /**
     * @brief Updates an existing dog's data.
     * @param id The ID of the dog to update.
     * @param newDogData The new data to apply.
     * @return true if dog was found and updated, false otherwise.
     * @post The dog's data is modified and file is updated if found.
     */
    void updateDog(int id, const Dog& newDogData);

    // --- Accessors ---

    /**
     * @brief Gets all dogs in the repository.
     * @return Const reference to the internal vector of dogs.
     */
    const vector<Dog>& getAllDogs() const;

    /**
     * @brief Finds a dog by ID (non-const version).
     * @param id The ID to search for.
     * @return Pointer to the Dog if found, nullptr otherwise.
     */
    Dog* findDogById(int id);

    /**
     * @brief Finds a dog by data (name, breed, age).
     * @param name The name to search for.
     * @param breed The breed to search for.
     * @param age The age to search for.
     * @return Const pointer to the Dog if found, nullptr otherwise.
     */
    const Dog* findDogByData(string name, string breed, int age) const;

    /**
     * @brief Finds a dog by ID (const version).
     * @param id The ID to search for.
     * @return Const pointer to the Dog if found, nullptr otherwise.
     */
    const Dog* findDogById(int id) const;

    // --- Utility ---

    /**
     * @brief Checks if a dog with given data exists.
     * @param name The name to check.
     * @param breed The breed to check.
     * @param age The age to check.
     * @return true if dog exists, false otherwise.
     */
    bool exists_for_add(string name, string breed, int age) const;

    /**
     * @brief Checks if a dog with given ID exists.
     * @param id The ID to check.
     * @return true if dog exists, false otherwise.
     */
    bool exists(int id) const;

    /**
     * @brief Gets the current number of dogs in repository.
     * @return The number of dogs stored.
     */
    int getSize() const;
};
