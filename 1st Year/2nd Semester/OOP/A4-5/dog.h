#pragma once
#include <string>

/**
 * @brief Represents a dog with an ID, name, breed, age, and photograph.
 */
class Dog {
private:
    int id;
    std::string name;
    std::string breed;
    int age;
    std::string photograph;

public:
    /**
     * @brief Default constructor.
     * @post id = 0, name = "", breed = "", age = 0, photograph = "".
     */
    Dog();

    /**
     * @brief Parameterized constructor.
     * @param id Unique identifier for the dog.
     * @param name The name of the dog.
     * @param breed The breed of the dog.
     * @param age The age of the dog.
     * @param photograph Link/path to the dog's photograph.
     * @post All fields are initialized with the given values.
     */
    Dog(int id, std::string name, std::string breed, int age, std::string photograph);

    // --- Getters ---

    /**
     * @brief Gets the dog's ID.
     * @return The id of the dog.
     */
    int getId() const;

    /**
     * @brief Gets the dog's name.
     * @return The name of the dog.
     */
    std::string getName() const;

    /**
     * @brief Gets the dog's breed.
     * @return The breed of the dog.
     */
    std::string getBreed() const;

    /**
     * @brief Gets the dog's age.
     * @return The age of the dog.
     */
    int getAge() const;

    /**
     * @brief Gets the dog's photograph link/path.
     * @return The photograph of the dog.
     */
    std::string getPhotograph() const;

    // --- Setters ---

    /**
     * @brief Sets the dog's name.
     * @param newName The new name to assign.
     * @post name = newName.
     */
    void setName(const std::string& newName);

    /**
     * @brief Sets the dog's breed.
     * @param newBreed The new breed to assign.
     * @post breed = newBreed.
     */
    void setBreed(const std::string& newBreed);

    /**
     * @brief Sets the dog's age.
     * @param newAge The new age to assign.
     * @post age = newAge.
     */
    void setAge(int newAge);

    /**
     * @brief Sets the dog's photograph link/path.
     * @param newPhoto The new photograph to assign.
     * @post photograph = newPhoto.
     */
    void setPhotograph(const std::string& newPhoto);

    // --- Operator Overload ---

    /**
     * @brief Compares two dogs by ID.
     * @param other The dog to compare with.
     * @return true if IDs are equal, false otherwise.
     */
    bool operator==(const Dog& other) const {
        return id == other.id;
    }
};