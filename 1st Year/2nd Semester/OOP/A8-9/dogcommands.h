#pragma once
#include "command.h"
#include "service.h"
#include <string>
#include <memory>

// Forward declaration
class AdminWidget;

// Base class for dog-related commands
class DogCommand : public Command {
protected:
    DogService* service;
    AdminWidget* widget;

public:
    DogCommand(DogService* service, AdminWidget* widget);
    virtual ~DogCommand() = default;
};

// Command for adding a dog
class AddDogCommand : public DogCommand {
private:
    std::string name;
    std::string breed;
    int age;
    std::string photograph;
    int addedDogId;
    bool dogAdded;

public:
    AddDogCommand(DogService* service, AdminWidget* widget,
        const std::string& name, const std::string& breed,
        int age, const std::string& photograph);

    void execute() override;
    void undo() override;
    std::unique_ptr<Command> clone() const override;
};

// Command for removing a dog
class RemoveDogCommand : public DogCommand {
private:
    int dogId;
    Dog removedDog; // Store the removed dog for undo
    bool dogStored;

public:
    RemoveDogCommand(DogService* service, AdminWidget* widget, int dogId);

    void execute() override;
    void undo() override;
    std::unique_ptr<Command> clone() const override;
};

// Command for updating a dog
class UpdateDogCommand : public DogCommand {
private:
    int dogId;
    std::string newName, newBreed, newPhotograph;
    int newAge;
    Dog originalDog; // Store original dog data for undo
    bool originalStored;

public:
    UpdateDogCommand(DogService* service, AdminWidget* widget,
        int dogId, const std::string& name, const std::string& breed,
        int age, const std::string& photograph);

    void execute() override;
    void undo() override;
    std::unique_ptr<Command> clone() const override;
};