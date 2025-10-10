#include "tests.h"

void DogTest::testAll() {
    std::cout << "Running all Dog tests...\n";

    testDefaultConstructor();
    testParameterizedConstructor();
    testSetBreed();
    testSetName();
    testSetAge();
    testSetPhotograph();

    std::cout << "All Dog tests completed.\n";
}

void DogTest::testDefaultConstructor() {
    Dog dog;

    bool passed =
        dog.getId() == 0 &&
        dog.getName() == "" &&
        dog.getBreed() == "" &&
        dog.getAge() == 0 &&
        dog.getPhotograph() == "";
}

void DogTest::testParameterizedConstructor() {
    int id = 1;
    std::string name = "Rex";
    std::string breed = "German Shepherd";
    int age = 3;
    std::string photograph = "rex.jpg";

    Dog dog(id, name, breed, age, photograph);

    bool passed =
        dog.getId() == id &&
        dog.getName() == name &&
        dog.getBreed() == breed &&
        dog.getAge() == age &&
        dog.getPhotograph() == photograph;
}

void DogTest::testSetBreed() {
    Dog dog(1, "Rex", "German Shepherd", 3, "rex.jpg");

    // Test normal case
    std::string newBreed = "Labrador";
    dog.setBreed(newBreed);
    bool normalCase = dog.getBreed() == newBreed;

    // Test empty string
    dog.setBreed("");
    bool emptyCase = dog.getBreed() == "";

    // Test long breed name
    std::string longBreed = "Very Long Breed Name That Could Potentially Cause Issues";
    dog.setBreed(longBreed);
    bool longCase = dog.getBreed() == longBreed;
}

void DogTest::testSetName() {
    Dog dog(1, "Rex", "German Shepherd", 3, "rex.jpg");

    // Test normal case
    std::string newName = "Max";
    dog.setName(newName);
    bool normalCase = dog.getName() == newName;

    // Test empty string
    dog.setName("");
    bool emptyCase = dog.getName() == "";

    // Test long name
    std::string longName = "Very Long Dog Name That Could Potentially Cause Issues";
    dog.setName(longName);
    bool longCase = dog.getName() == longName;
}

void DogTest::testSetAge() {
    Dog dog(1, "Rex", "German Shepherd", 3, "rex.jpg");

    // Test normal case
    int newAge = 5;
    dog.setAge(newAge);
    bool normalCase = dog.getAge() == newAge;

    // Test zero
    dog.setAge(0);
    bool zeroCase = dog.getAge() == 0;

    // Test negative value (implementation dependent)
    dog.setAge(-1);
    bool negativeCase = true; // Adjust based on expected behavior

    // Test large value
    dog.setAge(20);
    bool largeCase = dog.getAge() == 20;
}

void DogTest::testSetPhotograph() {
    Dog dog(1, "Rex", "German Shepherd", 3, "rex.jpg");

    // Test normal case
    std::string newPhoto = "max.jpg";
    dog.setPhotograph(newPhoto);
    bool normalCase = dog.getPhotograph() == newPhoto;

    // Test empty string
    dog.setPhotograph("");
    bool emptyCase = dog.getPhotograph() == "";

    // Test long path
    std::string longPath = "very/long/path/to/photograph/that/could/cause/issues/dog.jpg";
    dog.setPhotograph(longPath);
    bool longCase = dog.getPhotograph() == longPath;

}


// DynamicVectorTest implementations
void DynamicVectorTest::testAll() {
    testConstructor();
    testCopyConstructor();
    testAssignmentOperator();
    testAdd();
    testRemove();
    testSearch();
    testSize();
    testIsEmpty();
    testIndexOperator();
    std::cout << "All DynamicVector tests passed!" << std::endl;
}

void DynamicVectorTest::testConstructor() {
    DynamicVector<int> v;
    assert(v.size() == 0);
    assert(v.isEmpty() == true);
}

void DynamicVectorTest::testCopyConstructor() {
    DynamicVector<int> v;
    v.add(1);
    v.add(2);
    v.add(3);

    DynamicVector<int> v2(v);
    assert(v2.size() == 3);
    assert(v2[0] == 1);
    assert(v2[1] == 2);
    assert(v2[2] == 3);
}

void DynamicVectorTest::testAssignmentOperator() {
    DynamicVector<int> v;
    v.add(1);
    v.add(2);

    DynamicVector<int> v2;
    v2 = v;
    assert(v2.size() == 2);
    assert(v2[0] == 1);
    assert(v2[1] == 2);

    // Self-assignment
    v = v;
    assert(v.size() == 2);
    assert(v[0] == 1);
    assert(v[1] == 2);
}

void DynamicVectorTest::testAdd() {
    DynamicVector<int> v;
    v.add(1);
    assert(v.size() == 1);
    assert(v[0] == 1);

    // Test resize
    for (int i = 2; i <= 10; i++) {
        v.add(i);
    }
    assert(v.size() == 10);
    for (int i = 0; i < 10; i++) {
        assert(v[i] == i + 1);
    }
}

void DynamicVectorTest::testRemove() {
    DynamicVector<int> v;
    v.add(1);
    v.add(2);
    v.add(3);

    bool result = v.remove(2);
    assert(result == true);
    assert(v.size() == 2);
    assert(v[0] == 1);
    assert(v[1] == 3);

    result = v.remove(5); // Non-existent element
    assert(result == false);
    assert(v.size() == 2);
}

void DynamicVectorTest::testSearch() {
    DynamicVector<int> v;
    v.add(1);
    v.add(2);
    v.add(3);

    assert(v.search(2) == true);
    assert(v.search(5) == false);
}

void DynamicVectorTest::testSize() {
    DynamicVector<int> v;
    assert(v.size() == 0);

    v.add(1);
    v.add(2);
    assert(v.size() == 2);

    v.remove(1);
    assert(v.size() == 1);
}

void DynamicVectorTest::testIsEmpty() {
    DynamicVector<int> v;
    assert(v.isEmpty() == true);

    v.add(1);
    assert(v.isEmpty() == false);

    v.remove(1);
    assert(v.isEmpty() == true);
}

void DynamicVectorTest::testIndexOperator() {
    DynamicVector<int> v;
    v.add(10);
    v.add(20);

    assert(v[0] == 10);
    assert(v[1] == 20);

    v[0] = 30; // Test assignment
    assert(v[0] == 30);

    // Test out of bounds
    try {
        v[2]; // This should throw an exception
        assert(false); // Should not reach here
    }
    catch (const std::out_of_range&) {
        // Expected exception
    }
}

// RepositoryTest implementations
void RepositoryTest::testAll() {
    testAddDog();
    testRemoveDog();
    testUpdateDog();
    testGetAllDogs();
    testFindDogById();
    testExists();
    testGetSize();
    std::cout << "All Repository tests passed!" << std::endl;
}

void RepositoryTest::testAddDog() {
    Repository repo;
    Dog dog1(1, "Rex", "German Shepherd", 3, "photo1.jpg");
    Dog dog2(2, "Max", "Labrador", 2, "photo2.jpg");

    bool result = repo.addDog(dog1);
    assert(result == true);
    assert(repo.getSize() == 1);

    result = repo.addDog(dog2);
    assert(result == true);
    assert(repo.getSize() == 2);

    Dog dog3(1, "Rex", "German Shepherd", 3, "photo1.jpg");
    result = repo.addDog(dog3);
    assert(result == false);
    assert(repo.getSize() == 2);
}

void RepositoryTest::testRemoveDog() {
    Repository repo;
    Dog dog1(1, "Rex", "German Shepherd", 3, "photo1.jpg");
    Dog dog2(2, "Max", "Labrador", 2, "photo2.jpg");

    repo.addDog(dog1);
    repo.addDog(dog2);

    bool result = repo.removeDog(1);
    assert(result == true);
    assert(repo.getSize() == 1);

    result = repo.removeDog(3);
    assert(result == false);
    assert(repo.getSize() == 1);
}

void RepositoryTest::testUpdateDog() {
    Repository repo;
    Dog dog1(1, "Rex", "German Shepherd", 3, "photo1.jpg");
    repo.addDog(dog1);

    Dog updatedDog(1, "Rex Updated", "German Shepherd Updated", 4, "photo1_updated.jpg");
    bool result = repo.updateDog(1, updatedDog);
    assert(result == true);

    Dog* found = repo.findDogById(1);
    assert(found != nullptr);
    assert(found->getName() == "Rex Updated");
    assert(found->getBreed() == "German Shepherd Updated");
    assert(found->getAge() == 4);
    assert(found->getPhotograph() == "photo1_updated.jpg");

    result = repo.updateDog(3, updatedDog);
    assert(result == false);
}

void RepositoryTest::testGetAllDogs() {
    Repository repo;
    Dog dog1(1, "Rex", "German Shepherd", 3, "photo1.jpg");
    Dog dog2(2, "Max", "Labrador", 2, "photo2.jpg");

    repo.addDog(dog1);
    repo.addDog(dog2);

    DynamicVector<Dog> allDogs = repo.getAllDogs();
    assert(allDogs.size() == 2);
    assert(allDogs[0].getId() == 1);
    assert(allDogs[1].getId() == 2);
}

void RepositoryTest::testFindDogById() {
    Repository repo;
    Dog dog1(1, "Rex", "German Shepherd", 3, "photo1.jpg");
    repo.addDog(dog1);

    Dog* found = repo.findDogById(1);
    assert(found != nullptr);
    assert(found->getId() == 1);
    assert(found->getName() == "Rex");

    found = repo.findDogById(2);
    assert(found == nullptr);
}

void RepositoryTest::testExists() {
    Repository repo;
    Dog dog1(1, "Rex", "German Shepherd", 3, "photo1.jpg");
    repo.addDog(dog1);

    assert(repo.exists(1) == true);
    assert(repo.exists(2) == false);
}

void RepositoryTest::testGetSize() {
    Repository repo;
    assert(repo.getSize() == 0);

    Dog dog1(1, "Rex", "German Shepherd", 3, "photo1.jpg");
    repo.addDog(dog1);
    assert(repo.getSize() == 1);

    Dog dog2(2, "Max", "Labrador", 2, "photo2.jpg");
    repo.addDog(dog2);
    assert(repo.getSize() == 2);

    repo.removeDog(1);
    assert(repo.getSize() == 1);
}

void ServiceTest::testAll() {
    testAddDog();
    testRemoveDog();
    testUpdateDog();
    testGetAllDogs();
    testGenerateSampleDogs();
    testNextIdInitialization();
    std::cout << "All Service tests passed!" << std::endl;
}

void ServiceTest::testAddDog() {
    Repository repo;
    DogService service(repo);

    std::string name = "Rex";
    std::string breed = "German Shepherd";
    int age = 3;
    std::string photo = "photo1.jpg";

    bool result = service.addDog(name, breed, age, photo);
    assert(result == true);
    assert(repo.getSize() == 1);

    DynamicVector<Dog> allDogs = service.getAllDogs();
    assert(allDogs.size() == 1);
    assert(allDogs[0].getName() == "Rex");
    assert(allDogs[0].getBreed() == "German Shepherd");
    assert(allDogs[0].getAge() == 3);
    assert(allDogs[0].getPhotograph() == "photo1.jpg");

    std::string name2 = "Max";
    std::string breed2 = "Labrador";
    int age2 = 2;
    std::string photo2 = "photo2.jpg";

    result = service.addDog(name2, breed2, age2, photo2);
    assert(result == true);
    assert(repo.getSize() == 2);
}

void ServiceTest::testRemoveDog() {
    Repository repo;
    DogService service(repo);

    std::string name = "Rex";
    std::string breed = "German Shepherd";
    int age = 3;
    std::string photo = "photo1.jpg";
    service.addDog(name, breed, age, photo);

    DynamicVector<Dog> allDogs = service.getAllDogs();
    int dogId = allDogs[0].getId();

    bool result = service.removeDog(dogId);
    assert(result == true);
    assert(repo.getSize() == 0);

    result = service.removeDog(999);
    assert(result == false);
}

void ServiceTest::testUpdateDog() {
    Repository repo;
    DogService service(repo);

    std::string name = "Rex";
    std::string breed = "German Shepherd";
    int age = 3;
    std::string photo = "photo1.jpg";
    service.addDog(name, breed, age, photo);

    DynamicVector<Dog> allDogs = service.getAllDogs();
    int dogId = allDogs[0].getId();

    std::string newName = "Rex Updated";
    std::string newBreed = "German Shepherd Updated";
    int newAge = 4;
    std::string newPhoto = "photo1_updated.jpg";

    bool result = service.updateDog(dogId, newName, newBreed, newAge, newPhoto);
    assert(result == true);

    allDogs = service.getAllDogs();
    assert(allDogs[0].getName() == "Rex Updated");
    assert(allDogs[0].getBreed() == "German Shepherd Updated");
    assert(allDogs[0].getAge() == 4);
    assert(allDogs[0].getPhotograph() == "photo1_updated.jpg");

    result = service.updateDog(999, newName, newBreed, newAge, newPhoto);
    assert(result == false);
}

void ServiceTest::testGetAllDogs() {
    Repository repo;
    DogService service(repo);

    DynamicVector<Dog> allDogs = service.getAllDogs();
    assert(allDogs.size() == 0);

    std::string name1 = "Rex";
    std::string breed1 = "German Shepherd";
    int age1 = 3;
    std::string photo1 = "photo1.jpg";
    service.addDog(name1, breed1, age1, photo1);

    std::string name2 = "Max";
    std::string breed2 = "Labrador";
    int age2 = 2;
    std::string photo2 = "photo2.jpg";
    service.addDog(name2, breed2, age2, photo2);

    allDogs = service.getAllDogs();
    assert(allDogs.size() == 2);
}

void ServiceTest::testGenerateSampleDogs() {
    Repository repo;
    DogService service(repo);

    assert(repo.getSize() == 0);
    service.generateSampleDogs();
    assert(repo.getSize() == 10);
}

void ServiceTest::testNextIdInitialization() {
    // Test case 1: Empty repository (should use default nextId = 223)
    {
        Repository repo;
        DogService service(repo);

        service.addDog("Test", "Test Breed", 1, "test.jpg");
        DynamicVector<Dog> dogs = service.getAllDogs();
        assert(dogs.size() == 1);
        assert(dogs[0].getId() == 223);

        // Adding another dog should use nextId = 224
        service.addDog("Test2", "Test Breed", 1, "test.jpg");
        dogs = service.getAllDogs();
        assert(dogs.size() == 2);
        assert(dogs[1].getId() == 224);
    }

    // Test case 2: Repository with dogs having IDs less than default nextId
    {
        Repository repo;
        // Add dogs with IDs less than 223
        repo.addDog(Dog(100, "Dog1", "Breed1", 1, "photo1.jpg"));
        repo.addDog(Dog(150, "Dog2", "Breed2", 2, "photo2.jpg"));
        repo.addDog(Dog(200, "Dog3", "Breed3", 3, "photo3.jpg"));

        DogService service(repo);

        // Adding a new dog should use nextId = 223 (default)
        service.addDog("Test", "Test Breed", 1, "test.jpg");
        DynamicVector<Dog> dogs = service.getAllDogs();
        assert(dogs.size() == 4);

        // Find the newly added dog and check its ID
        bool foundNewDog = false;
        for (int i = 0; i < dogs.size(); i++) {
            if (dogs[i].getName() == "Test") {
                assert(dogs[i].getId() == 223);
                foundNewDog = true;
                break;
            }
        }
        assert(foundNewDog);
    }

    // Test case 3: Repository with dogs having IDs greater than default nextId
    {
        Repository repo;
        // Add dogs with some IDs greater than 223
        repo.addDog(Dog(100, "Dog1", "Breed1", 1, "photo1.jpg"));
        repo.addDog(Dog(300, "Dog2", "Breed2", 2, "photo2.jpg")); // Higher than default
        repo.addDog(Dog(250, "Dog3", "Breed3", 3, "photo3.jpg")); // Higher than default

        DogService service(repo);

        // Adding a new dog should use nextId = 301 (300 + 1)
        service.addDog("Test", "Test Breed", 1, "test.jpg");
        DynamicVector<Dog> dogs = service.getAllDogs();
        assert(dogs.size() == 4);

        // Find the newly added dog and check its ID
        bool foundNewDog = false;
        for (int i = 0; i < dogs.size(); i++) {
            if (dogs[i].getName() == "Test") {
                assert(dogs[i].getId() == 301);
                foundNewDog = true;
                break;
            }
        }
        assert(foundNewDog);
    }

    // Test case 4: Repository with mixed IDs including the exact default nextId value
    {
        Repository repo;
        repo.addDog(Dog(100, "Dog1", "Breed1", 1, "photo1.jpg"));
        repo.addDog(Dog(223, "Dog2", "Breed2", 2, "photo2.jpg")); // Exactly the default
        repo.addDog(Dog(150, "Dog3", "Breed3", 3, "photo3.jpg"));

        DogService service(repo);

        // Adding a new dog should use nextId = 224 (223 + 1)
        service.addDog("Test", "Test Breed", 1, "test.jpg");
        DynamicVector<Dog> dogs = service.getAllDogs();
        assert(dogs.size() == 4);

        // Find the newly added dog and check its ID
        bool foundNewDog = false;
        for (int i = 0; i < dogs.size(); i++) {
            if (dogs[i].getName() == "Test") {
                assert(dogs[i].getId() == 224);
                foundNewDog = true;
                break;
            }
        }
        assert(foundNewDog);
    }
}

void runAllTests() {
    std::cout << "Running tests...\n";

    DogTest::testAll();
    DynamicVectorTest::testAll();
    RepositoryTest::testAll();
    ServiceTest::testAll();

    std::cout << "All tests passed successfully!\n";
}