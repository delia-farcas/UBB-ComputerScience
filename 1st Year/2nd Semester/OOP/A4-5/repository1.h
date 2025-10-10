#pragma once
#include "dynamic_vector.h"
#include "dog.h"

/**
 * @brief Repository class for managing Dog objects.
 *
 * Provides CRUD operations for Dog entities using a DynamicVector as storage.
 */
class Repository {
private:
    DynamicVector<Dog> dogs; ///< Internal storage for Dog objects

public:
    // --- Modifiers ---

    /**
     * @brief Adds a new dog to the repository.
     * @param dog The Dog object to add.
     * @return true if dog was added successfully, false if a dog with same ID already exists.
     * @post The dogs collection size increases by 1 if successful.
     */
    bool addDog(const Dog& dog);

    /**
     * @brief Removes a dog from the repository by ID.
     * @param id The ID of the dog to remove.
     * @return true if dog was found and removed, false otherwise.
     * @post The dogs collection size decreases by 1 if successful.
     */
    bool removeDog(int id);

    /**
     * @brief Updates an existing dog's data.
     * @param id The ID of the dog to update.
     * @param newDogData The new data to apply.
     * @return true if dog was found and updated, false otherwise.
     * @post The dog's data is modified if found.
     */
    bool updateDog(int id, const Dog& newDogData);

    // --- Accessors ---

    /**
     * @brief Gets all dogs in the repository.
     * @return Const reference to the internal DynamicVector of dogs.
     */
    const DynamicVector<Dog>& getAllDogs() const;

    /**
     * @brief Finds a dog by ID (non-const version).
     * @param id The ID to search for.
     * @return Pointer to the Dog if found, nullptr otherwise.
     */
    Dog* findDogById(int id);
    const Dog* findDogByData(std::string name, std::string breed, int age) const;

    /**
     * @brief Finds a dog by ID (const version).
     * @param id The ID to search for.
     * @return Const pointer to the Dog if found, nullptr otherwise.
     */
    const Dog* findDogById(int id) const;

    // --- Utility ---

    /**
     * @brief Checks if a dog with given ID exists.
     * @param id The ID to check.
     * @return true if dog exists, false otherwise.
     */
    bool exists_for_add(std::string name, std::string breed, int age) const;
    bool exists(int id) const;

    /**
     * @brief Gets the current number of dogs in repository.
     * @return The number of dogs stored.
     */
    int getSize() const;
};