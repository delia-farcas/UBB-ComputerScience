#include "service.h"

DogService::DogService(Repository& repo) : repository(repo), nextId(223) {
    const auto& allDogs = repository.getAllDogs();
    for (const Dog& dog : allDogs) {
        if (dog.getId() >= nextId) {
            nextId = dog.getId() + 1;
        }
    }
}

void DogService::addDog(const string& name, const string& breed,
    int age, const string& photograph) {
    try {
        repository.addDog(Dog(nextId++, name, breed, age, photograph));
    }
    catch (const ValidationException& e) {
        throw;
    }
    catch (const RepositoryException& e) {
        throw;
    }
}

void DogService::removeDog(int id) {
    try {
        repository.removeDog(id);
    }
    catch(const RepositoryException& e){
        throw;
    }
}

void DogService::updateDog(int id, const string& name, const string& breed, int age, const string& photograph) {
    try {
        repository.updateDog(id, Dog(id, name, breed, age, photograph));
    }
    catch (const RepositoryException& e) {
        throw;
    }
}

const vector<Dog>& DogService::getAllDogs() const {
    return repository.getAllDogs();
}

void DogService::generateSampleDogs() {
  
    Dog newDog1(123, "Bella", "Maltese", 2, "https://i.pinimg.com/736x/7b/3d/cd/7b3dcd0f95e6f30d2c326e0a9066a718.jpg");
    repository.addDog(newDog1);

    Dog newDog2(134, "Pixi", "Samoyed", 3, "https://i.pinimg.com/736x/b4/66/31/b4663179130a2ac441dcb99ef38d671c.jpg");
    repository.addDog(newDog2);

    Dog newDog3(137, "Pepe", "Yorkshire Terrier", 1, "https://i.pinimg.com/736x/fc/14/72/fc1472274291239f5d53da36ac23e93a.jpg");
    repository.addDog(newDog3);

    Dog newDog4(140, "Grivei", "Beagle", 4, "https://i.pinimg.com/736x/db/9d/ab/db9dab07f96f32d4ba333794dad86a6b.jpg");
    repository.addDog(newDog4);

    Dog newDog5(147, "Nora", "German Shepherd", 4, "https://i.pinimg.com/736x/b6/67/14/b667143861ed1542248dcf48b793ffc8.jpg");
    repository.addDog(newDog5);

    Dog newDog6(152, "Maya", "Maltese", 2, "https://i.pinimg.com/736x/37/06/36/370636361f3424579ae7b4693281c4c4.jpg");
    repository.addDog(newDog6);

    Dog newDog7(158, "Kai", "Shiba Inu", 3, "https://i.pinimg.com/736x/b2/7d/2d/b27d2d22ab6b6c7d9e7dfd862d607786.jpg");
    repository.addDog(newDog7);

    Dog newDog8(167, "Brie", "Golden Retriever", 0, "https://i.pinimg.com/736x/de/49/0a/de490a03adadb87ae5bc9368ed5df8eb.jpg");
    repository.addDog(newDog8);

    Dog newDog9(172, "Buzz", "Husky", 7, "https://i.pinimg.com/736x/d0/e4/90/d0e49067be39d21a040660a96d26237f.jpg");
    repository.addDog(newDog9);

    Dog newDog10(184, "Phoebe", "Pomeranian", 1, "https://i.pinimg.com/736x/4b/13/08/4b130824e3b8eb3dcfb8c24e9f318086.jpg");
    repository.addDog(newDog10);
}
