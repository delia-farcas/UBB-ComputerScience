#include "user_repository.h"

void UserRepository::adoptDog(const Dog& dog) {
    if (isAdopted(dog)) {
        throw RepositoryException("Dog already adopted!<3");
    }
    adoptionList.push_back(dog);
}

const vector<Dog>& UserRepository::getAdoptionList() const {
    return adoptionList;
}

bool UserRepository::isAdopted(const Dog& dog) const {
    for (const Dog adopted : adoptionList) {
        if (adopted.getId() == dog.getId())
            return true;
    }
    return false;
}

int UserRepository::getSize() const {
    return adoptionList.size();
}

