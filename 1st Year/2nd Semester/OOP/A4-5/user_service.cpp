#include "user_service.h"

UserService::UserService(Repository& repo) 
    : dogRepository(repo), currentDogIndex(0), isFiltered(false) {
}

const Dog* UserService::getCurrentDog() const {
    const DynamicVector<Dog>& dogs = isFiltered ? filteredDogs : dogRepository.getAllDogs();
    
    if (dogs.size() == 0) {
        return nullptr;
    }
    
    return &dogs[currentDogIndex];
}

void UserService::nextDog() {
    const DynamicVector<Dog>& dogs = isFiltered ? filteredDogs : dogRepository.getAllDogs();
    
    if (dogs.size() == 0) {
        return;
    }
    
    currentDogIndex = (currentDogIndex + 1) % dogs.size();
}

bool UserService::adoptCurrentDog() {
    const Dog* dog = getCurrentDog();
    if (!dog) {
        return false;
    }
    
    return adoptionRepository.adoptDog(*dog);
}

const DynamicVector<Dog>& UserService::getAdoptionList() const {
    return adoptionRepository.getAdoptionList();
}

void UserService::filterDogs(const std::string& breed, int maxAge) {
    const DynamicVector<Dog>& allDogs = dogRepository.getAllDogs();
    filteredDogs = DynamicVector<Dog>();
    
    for (int i = 0; i < allDogs.size(); i++) {
        const Dog& dog = allDogs[i];
        bool breedMatch = breed.empty() || dog.getBreed() == breed;
        bool ageMatch = dog.getAge() <= maxAge;
        
        if (breedMatch && ageMatch) {
            filteredDogs.add(dog);
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

