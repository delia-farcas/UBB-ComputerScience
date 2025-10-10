#pragma once
#include "dynamic_vector.h"
#include "dog.h"

/**
 * @brief Repository class for managing user's adopted dogs.
 * 
 * Provides operations for storing and retrieving adopted dogs.
 */
class UserRepository {
private:
    DynamicVector<Dog> adoptionList; 

public:
    /**
     * @brief Adds a dog to the adoption list.
     * @param dog The Dog object to add.
     * @return true if dog was added successfully, false if already in adoption list.
     * @post The adoption list size increases by 1 if successful.
     */
    bool adoptDog(const Dog& dog);

    /**
     * @brief Gets all dogs in the adoption list.
     * @return Const reference to the internal DynamicVector of adopted dogs.
     */
    const DynamicVector<Dog>& getAdoptionList() const;

    /**
     * @brief Checks if a dog is already in the adoption list.
     * @param dog The dog to check.
     * @return true if dog exists in adoption list, false otherwise.
     */
    bool isAdopted(const Dog& dog) const;

    /**
     * @brief Gets the current number of dogs in adoption list.
     * @return The number of adopted dogs.
     */
    int getSize() const;
};

