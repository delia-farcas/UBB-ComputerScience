#pragma once
#include "dog.h"
#include "dynamic_vector.h"
#include "repository1.h"
#include "service1.h"
#include <cassert>
#include <iostream>

/**
 * @brief Test class for Dog class functionality
 */
class DogTest {
public:
    /**
     * @brief Runs all Dog tests
     */
    static void testAll();

private:
    /**
     * @brief Tests default constructor functionality
     * @post Verifies default values are set correctly
     */
    static void testDefaultConstructor();

    /**
     * @brief Tests parameterized constructor functionality
     * @post Verifies all parameters are set correctly
     */
    static void testParameterizedConstructor();

    /**
     * @brief Tests breed setter functionality
     * @post Verifies breed is updated correctly
     */
    static void testSetBreed();

    /**
     * @brief Tests name setter functionality
     * @post Verifies name is updated correctly
     */
    static void testSetName();

    /**
     * @brief Tests age setter functionality
     * @post Verifies age is updated correctly
     */
    static void testSetAge();

    /**
     * @brief Tests photograph setter functionality
     * @post Verifies photograph is updated correctly
     */
    static void testSetPhotograph();
};

/**
 * @brief Test suite for DynamicVector class
 */
class DynamicVectorTest {
public:
    /**
     * @brief Runs all DynamicVector tests
     */
    static void testAll();

private:
    /**
     * @brief Tests default constructor functionality
     * @post Verifies initial capacity and size
     */
    static void testConstructor();

    /**
     * @brief Tests copy constructor functionality
     * @post Verifies deep copy is performed
     */
    static void testCopyConstructor();

    /**
     * @brief Tests assignment operator functionality
     * @post Verifies proper copying and self-assignment handling
     */
    static void testAssignmentOperator();

    /**
     * @brief Tests element addition functionality
     * @post Verifies size increase and automatic resizing
     */
    static void testAdd();

    /**
     * @brief Tests element removal functionality
     * @post Verifies size decrease and element shifting
     */
    static void testRemove();

    /**
     * @brief Tests element search functionality
     * @post Verifies correct element detection
     */
    static void testSearch();

    /**
     * @brief Tests size reporting functionality
     * @post Verifies accurate size reporting
     */
    static void testSize();

    /**
     * @brief Tests empty state detection
     * @post Verifies correct empty/full detection
     */
    static void testIsEmpty();

    /**
     * @brief Tests index operator functionality
     * @post Verifies element access and bounds checking
     */
    static void testIndexOperator();
};

/**
 * @brief Test suite for Repository class
 */
class RepositoryTest {
public:
    /**
     * @brief Runs all Repository tests
     */
    static void testAll();

private:
    /**
     * @brief Tests dog addition functionality
     * @post Verifies successful addition and duplicate prevention
     */
    static void testAddDog();

    /**
     * @brief Tests dog removal functionality
     * @post Verifies successful removal and missing dog handling
     */
    static void testRemoveDog();

    /**
     * @brief Tests dog update functionality
     * @post Verifies field updates and invalid update handling
     */
    static void testUpdateDog();

    /**
     * @brief Tests dog collection retrieval
     * @post Verifies complete collection access
     */
    static void testGetAllDogs();

    /**
     * @brief Tests dog search by ID functionality
     * @post Verifies correct dog retrieval and null returns
     */
    static void testFindDogById();

    /**
     * @brief Tests dog existence checking
     * @post Verifies accurate existence reporting
     */
    static void testExists();

    /**
     * @brief Tests size reporting functionality
     * @post Verifies accurate count of stored dogs
     */
    static void testGetSize();
};

/**
 * @brief Test suite for Service class
 */
class ServiceTest {
public:
    /**
     * @brief Runs all Service tests
     */
    static void testAll();

private:
    /**
     * @brief Tests service-layer dog addition
     * @post Verifies validation and automatic ID assignment
     */
    static void testAddDog();

    /**
     * @brief Tests service-layer dog removal
     * @post Verifies proper repository interaction
     */
    static void testRemoveDog();

    /**
     * @brief Tests service-layer dog updates
     * @post Verifies partial updates and validation
     */
    static void testUpdateDog();

    /**
     * @brief Tests dog collection retrieval
     * @post Verifies proper data access
     */
    static void testGetAllDogs();

    /**
     * @brief Tests sample data generation
     * @post Verifies repository population
     */
    static void testGenerateSampleDogs();

    /**
    * @brief Tests id initialization
    * @post verifies if the id is given correctly
    */
    static void testNextIdInitialization();
};

/**
 * @brief Executes all test suites
 * @post Runs all DynamicVector, Repository and Service tests
 */
void runAllTests();