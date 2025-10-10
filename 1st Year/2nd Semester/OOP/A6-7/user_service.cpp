#include "user_service.h"

UserService::UserService(Repository& repo, AdoptionList& adoptionList)
    : dogRepository(repo), adoptionList(adoptionList), currentDogIndex(0), isFiltered(false) {
}

const Dog* UserService::getCurrentDog() const {
    const vector<Dog>& dogs = isFiltered ? filteredDogs : dogRepository.getAllDogs();

    if (dogs.size() == 0) {
        return nullptr;
    }

    return &dogs[currentDogIndex];
}

void UserService::nextDog() {
    const vector<Dog>& dogs = isFiltered ? filteredDogs : dogRepository.getAllDogs();

    if (dogs.size() == 0) {
        return;
    }

    currentDogIndex = (currentDogIndex + 1) % dogs.size();
}

void UserService::adoptCurrentDog() {
    const Dog* dog = getCurrentDog();
    if (!dog) {
        throw RepositoryException("No dog");
    }
    try {
        adoptionRepository.adoptDog(*dog);
        adoptionList.save(*dog);
    }
    catch (const RepositoryException& e) {
        throw;
    }
}

const vector<Dog>& UserService::getAdoptionList() const {
    return adoptionRepository.getAdoptionList();
}

void UserService::displayAdoptionList() const {
    adoptionList.displayList();
}

void UserService::filterDogs(const string& breed, int maxAge) {
    const vector<Dog>& allDogs = dogRepository.getAllDogs();
    filteredDogs = vector<Dog>();

    for (int i = 0; i < allDogs.size(); i++) {
        const Dog& dog = allDogs[i];
        bool breedMatch = breed.empty() || dog.getBreed() == breed;
        bool ageMatch = dog.getAge() <= maxAge;

        if (breedMatch && ageMatch) {
            filteredDogs.push_back(dog);
        }
    }

    isFiltered = true;
    currentDogIndex = 0;
}

void UserService::clearFilter() {
    isFiltered = false;
    currentDogIndex = 0;
}

bool UserService::isAdopted(const Dog& dog) const {
    return adoptionRepository.isAdopted(dog);
}

int UserService::getDogCount() const {
    return isFiltered ? filteredDogs.size() : dogRepository.getAllDogs().size();
}
