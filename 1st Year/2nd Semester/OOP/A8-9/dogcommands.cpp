#include "dogcommands.h"
#include "adminwidget.h"

// DogCommand implementation
DogCommand::DogCommand(DogService* service, AdminWidget* widget)
    : service(service), widget(widget) {
}

// AddDogCommand implementation
AddDogCommand::AddDogCommand(DogService* service, AdminWidget* widget,
    const std::string& name, const std::string& breed,
    int age, const std::string& photograph)
    : DogCommand(service, widget), name(name), breed(breed), age(age),
    photograph(photograph), addedDogId(-1), dogAdded(false) {
}

void AddDogCommand::execute() {
    // Store the current state before adding
    const auto& dogsBefore = service->getAllDogs();
    int maxIdBefore = -1;

    // Find the highest ID before adding
    for (const auto& dog : dogsBefore) {
        if (dog.getId() > maxIdBefore) {
            maxIdBefore = dog.getId();
        }
    }

    // Add the dog
    service->addDog(name, breed, age, photograph);

    // Find the newly added dog (should have the highest ID)
    const auto& dogsAfter = service->getAllDogs();
    int maxIdAfter = -1;

    for (const auto& dog : dogsAfter) {
        if (dog.getId() > maxIdAfter) {
            maxIdAfter = dog.getId();
        }
    }

    // If we found a new highest ID, that's our added dog
    if (maxIdAfter > maxIdBefore) {
        addedDogId = maxIdAfter;
        dogAdded = true;
    }

    widget->refreshTable();
}

void AddDogCommand::undo() {
    if (dogAdded && addedDogId != -1) {
        try {
            service->removeDog(addedDogId);
            dogAdded = false; // Reset flag after successful undo
            widget->refreshTable();
        }
        catch (const std::exception& e) {
            // Handle exception if dog can't be removed
        }
    }
}

std::unique_ptr<Command> AddDogCommand::clone() const {
    return std::make_unique<AddDogCommand>(service, widget, name, breed, age, photograph);
}

// RemoveDogCommand implementation
RemoveDogCommand::RemoveDogCommand(DogService* service, AdminWidget* widget, int dogId)
    : DogCommand(service, widget), dogId(dogId), dogStored(false) {
}

void RemoveDogCommand::execute() {
    // Store the dog before removing it
    try {
        removedDog = service->getDogById(dogId);
        dogStored = true;
        service->removeDog(dogId);
        widget->refreshTable();
    }
    catch (const std::exception& e) {
        dogStored = false;
        throw;
    }
}

void RemoveDogCommand::undo() {
    if (dogStored) {
        // Use addDogWithId to restore the dog with its original ID
        service->addDogWithId(removedDog);
        widget->refreshTable();
    }
}

std::unique_ptr<Command> RemoveDogCommand::clone() const {
    return std::make_unique<RemoveDogCommand>(service, widget, dogId);
}

// UpdateDogCommand implementation
UpdateDogCommand::UpdateDogCommand(DogService* service, AdminWidget* widget,
    int dogId, const std::string& name, const std::string& breed,
    int age, const std::string& photograph)
    : DogCommand(service, widget), dogId(dogId), newName(name), newBreed(breed),
    newAge(age), newPhotograph(photograph), originalStored(false) {
}

void UpdateDogCommand::execute() {
    // Store original dog data before updating
    try {
        originalDog = service->getDogById(dogId);
        originalStored = true;
        service->updateDog(dogId, newName, newBreed, newAge, newPhotograph);
        widget->refreshTable();
    }
    catch (const std::exception& e) {
        originalStored = false;
        throw;
    }
}

void UpdateDogCommand::undo() {
    if (originalStored) {
        service->updateDog(dogId, originalDog.getName(), originalDog.getBreed(),
            originalDog.getAge(), originalDog.getPhotograph());
        widget->refreshTable();
    }
}

std::unique_ptr<Command> UpdateDogCommand::clone() const {
    return std::make_unique<UpdateDogCommand>(service, widget, dogId, newName, newBreed, newAge, newPhotograph);
}
