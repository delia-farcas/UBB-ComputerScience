#pragma once
#include "repository1.h"
#include "user_repository.h"

/**
 * @brief Service layer for user operations with dogs.
 *
 * Provides business logic for browsing dogs, filtering, and adoption.
 */
class UserService {
private:
    Repository& dogRepository;       ///< Reference to the dog repository
    UserRepository adoptionRepository; ///< Repository for adopted dogs
    int currentDogIndex;             ///< Index of the currently viewed dog
    DynamicVector<Dog> filteredDogs; ///< Dogs filtered by criteria
    bool isFiltered;                 ///< Flag indicating if filtering is active

public:
    /**
     * @brief Constructs a UserService with a repository reference.
     * @param repo Reference to the Repository containing all dogs.
     * @post Initializes currentDogIndex to 0, isFiltered to false.
     */
    explicit UserService(Repository& repo);

    /**
     * @brief Gets the current dog being viewed.
     * @return Pointer to the current Dog, nullptr if no dogs available.
     */
    const Dog* getCurrentDog() const;

    /**
     * @brief Moves to the next dog in the list.
     * @post Updates currentDogIndex, wrapping around to 0 if at the end.
     */
    void nextDog();

    /**
     * @brief Adopts the current dog.
     * @return true if adoption was successful, false if already adopted.
     * @post Adds current dog to adoption list if successful.
     */
    bool adoptCurrentDog();

    /**
     * @brief Gets all dogs in the adoption list.
     * @return Const reference to the adoption list.
     */
    const DynamicVector<Dog>& getAdoptionList() const;

    /**
     * @brief Filters dogs by breed and maximum age.
     * @param breed The breed to filter by (empty string for all breeds).
     * @param maxAge The maximum age to filter by.
     * @post Updates filteredDogs with matching dogs, sets isFiltered to true.
     */
    void filterDogs(const std::string& breed, int maxAge);

    /**
     * @brief Clears any active filters.
     * @post Sets isFiltered to false, resets currentDogIndex to 0.
     */
    void clearFilter();

    /**
     * @brief Checks if a dog is already adopted.
     * @param dog The dog to check.
     * @return true if dog is in adoption list, false otherwise.
     */
    bool isAdopted(const Dog& dog) const;

    /**
     * @brief Gets the number of dogs available (filtered or all).
     * @return The number of dogs in the current view.
     */
    int getDogCount() const;
};

