#pragma once
#include "repository.h"
#include <vector>
using namespace std;

/**
 * @brief Service layer for managing Dog entities.
 *
 * Provides business logic operations for Dog management,
 * acting as an intermediary between the UI and Repository layers.
 */
class DogService {
private:
    Repository& repository;  ///< Reference to the associated repository
    int nextId;             ///< Tracks the next available ID for new dogs

public:
    /**
     * @brief Constructs a DogService with a repository reference.
     * @param repo Reference to the Repository to use for persistence.
     * @post Initializes nextId based on existing dogs in repository.
     */
    explicit DogService(Repository& repo);

    // --- Dog Management ---

    /**
     * @brief Adds a new dog with automatic ID assignment.
     * @param name The dog's name.
     * @param breed The dog's breed.
     * @param age The dog's age.
     * @param photograph URL/path to the dog's photo.
     * @return true if dog was added successfully, false if validation failed.
     * @post On success: repository size increases by 1, nextId increments.
     */
    void addDog(const string& name, const string& breed,
        int age, const string& photograph);
    void addDogWithId(const Dog& dog);
    /**
     * @brief Removes a dog by ID.
     * @param id The ID of the dog to remove.
     * @return true if dog was found and removed, false otherwise.
     * @post On success: repository size decreases by 1.
     */
    void removeDog(int id);

    /**
     * @brief Updates a dog's information.
     * @param id The ID of the dog to update.
     * @param name New name (empty to keep current).
     * @param breed New breed (empty to keep current).
     * @param age New age (negative to keep current).
     * @param photograph New photo (empty to keep current).
     * @return true if dog was found and updated, false otherwise.
     * @post Only non-empty/negative parameters update existing values.
     */
    void updateDog(int id, const string& name,
        const string& breed, int age,
        const string& photograph);

    // --- Data Access ---

    /**
     * @brief Retrieves all dogs in the system.
     * @return Const reference to the collection of all dogs.
     */
    const vector<Dog>& getAllDogs() const;
    Dog getDogById(int id) const;

    // --- Utility ---

    /**
     * @brief Populates the repository with sample data.
     * @post Adds several predefined Dog objects to the repository.
     */
    void generateSampleDogs();
};