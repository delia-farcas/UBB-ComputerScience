#include "tests_user.h"
#include "user_repository.h"
#include "user_service.h"
#include "repository1.h"
#include <cassert>
#include <iostream>

bool runUserTests() {
    std::cout << "Running user mode tests...\n";
    
    bool repoTests = testUserRepository();
    bool serviceTests = testUserService();
    
    if (repoTests && serviceTests) {
        std::cout << "All user mode tests passed!\n";
        return true;
    } /*else {
        std::cout << "Some user mode tests failed!\n";
        return false;
    }
      */
}

bool testUserRepository() {
    UserRepository repo;
    
    // Test initial state
    assert(repo.getSize() == 0);
    assert(repo.getAdoptionList().size() == 0);
    
    // Test adopting a dog
    Dog dog1(1, "Rex", "German Shepherd", 3, "photo1.jpg");
    assert(repo.adoptDog(dog1) == true);
    assert(repo.getSize() == 1);
    
    // Test adopting the same dog again (should fail)
    assert(repo.adoptDog(dog1) == false);
    assert(repo.getSize() == 1);
    
    // Test adopting another dog
    Dog dog2(2, "Buddy", "Golden Retriever", 2, "photo2.jpg");
    assert(repo.adoptDog(dog2) == true);
    assert(repo.getSize() == 2);
    
    // Test isAdopted
    assert(repo.isAdopted(dog1) == true);
    assert(repo.isAdopted(dog2) == true);
    
    Dog dog3(3, "Max", "Beagle", 4, "photo3.jpg");
    assert(repo.isAdopted(dog3) == false);
    
    return true;
}

bool testUserService() {
    Repository dogRepo;

    // Test with empty repository (null case)
    UserService emptyService(dogRepo);
    assert(emptyService.getCurrentDog() == nullptr);
    assert(emptyService.getDogCount() == 0);

    // Add some test dogs
    Dog dog1(1, "Rex", "German Shepherd", 3, "photo1.jpg");
    Dog dog2(2, "Buddy", "Golden Retriever", 2, "photo2.jpg");
    Dog dog3(3, "Max", "Beagle", 4, "photo3.jpg");
    Dog dog4(4, "Charlie", "German Shepherd", 1, "photo4.jpg");
    Dog dog5(5, "Luna", "Poodle", 5, "photo5.jpg");

    dogRepo.addDog(dog1);
    dogRepo.addDog(dog2);
    dogRepo.addDog(dog3);
    dogRepo.addDog(dog4);
    dogRepo.addDog(dog5);

    UserService service(dogRepo);

    // Test initial state
    assert(service.getDogCount() == 5);
    assert(service.getCurrentDog()->getId() == 1);

    // Test nextDog
    service.nextDog();
    assert(service.getCurrentDog()->getId() == 2);

    service.nextDog();
    assert(service.getCurrentDog()->getId() == 3);

    service.nextDog();
    assert(service.getCurrentDog()->getId() == 4);

    // Test cycling back to first dog
    service.nextDog();
    service.nextDog();
    assert(service.getCurrentDog()->getId() == 1);

    // Test adoption
    assert(service.adoptCurrentDog() == true);
    assert(service.getAdoptionList().size() == 1);

    // Test isAdopted function
    assert(service.isAdopted(dog1) == true);
    assert(service.isAdopted(dog2) == false);
    assert(service.isAdopted(dog3) == false);

    // Test adopting the same dog again (should fail)
    assert(service.adoptCurrentDog() == false);
    assert(service.getAdoptionList().size() == 1);

    // Test filtering by breed
    service.filterDogs("German Shepherd", 10);
    assert(service.getDogCount() == 2);
    assert(service.getCurrentDog()->getBreed() == "German Shepherd");

    // Test filtering by age
    service.filterDogs("", 2);
    assert(service.getDogCount() == 2);

    // Test filtering by breed and age
    service.filterDogs("German Shepherd", 1);
    assert(service.getDogCount() == 1);
    assert(service.getCurrentDog()->getName() == "Charlie");

    // Test filtering with no matches (null case)
    service.filterDogs("Non-existent Breed", 0);
    assert(service.getDogCount() == 0);
    assert(service.getCurrentDog() == nullptr);

    // Test nextDog with empty filtered list (should not crash)
    service.nextDog();
    assert(service.getCurrentDog() == nullptr);

    // Test adoptCurrentDog with null current dog (should return false)
    assert(service.adoptCurrentDog() == false);

    service.clearFilter();
    assert(service.getDogCount() == 5);
    assert(service.getCurrentDog() != nullptr);

    // Test adopting multiple dogs and checking isAdopted
    service.nextDog(); // Move to dog2
    assert(service.adoptCurrentDog() == true);
    assert(service.isAdopted(dog2) == true);
    assert(service.getAdoptionList().size() == 2);

    // Adopt all remaining dogs
    service.nextDog(); // Move to dog3
    assert(service.adoptCurrentDog() == true);
    service.nextDog(); // Move to dog4
    assert(service.adoptCurrentDog() == true);
    service.nextDog(); // Move to dog5
    assert(service.adoptCurrentDog() == true);

    // Verify all dogs are adopted
    assert(service.isAdopted(dog1) == true);
    assert(service.isAdopted(dog2) == true);
    assert(service.isAdopted(dog3) == true);
    assert(service.isAdopted(dog4) == true);
    assert(service.isAdopted(dog5) == true);
    assert(service.getAdoptionList().size() == 5);

    return true;
}

