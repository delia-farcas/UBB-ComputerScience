#include "user_repository.h"

bool UserRepository::adoptDog(const Dog& dog) {
    if (isAdopted(dog))
        return false;
    adoptionList.add(dog);
    return true;
}

const DynamicVector<Dog>& UserRepository::getAdoptionList() const {
    return adoptionList;
}

bool UserRepository::isAdopted(const Dog& dog) const {
    for (int i = 0; i < adoptionList.size(); i++) {
        if (adoptionList[i].getId() == dog.getId())
            return true;
    }
    return false;
}

int UserRepository::getSize() const {
    return adoptionList.size();
}

