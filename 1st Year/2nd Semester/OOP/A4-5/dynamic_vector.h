#pragma once
#include <stdexcept>
#include <utility> 

/**
 * @brief A dynamic array implementation that automatically resizes when full.
 * @tparam TElem The type of elements stored in the vector.
 */
template <typename TElem>
class DynamicVector {
private:
    int nr_elem;     
    int capacity;   
    TElem* arr;      

    /**
     * @brief Doubles the capacity of the vector when full.
     * @post capacity *= 2, all elements are moved to new memory.
     */
    void resize();

public:
    // --- Constructors & Destructors ---

    /**
     * @brief Default constructor.
     * @post Creates empty vector with capacity = 5.
     */
    DynamicVector();

    /**
     * @brief Copy constructor.
     * @param other Vector to copy from.
     * @post Creates a deep copy of the other vector.
     */
    DynamicVector(const DynamicVector& other);

    /**
     * @brief Move constructor.
     * @param other Vector to move from.
     * @post Steals resources from 'other', leaving it empty.
     */
    DynamicVector(DynamicVector&& other) noexcept;

    /**
     * @brief Copy assignment operator.
     * @param other Vector to copy from.
     * @return Reference to this vector.
     * @post Performs deep copy, replaces current contents.
     */
    DynamicVector& operator=(const DynamicVector& other);

    /**
     * @brief Move assignment operator.
     * @param other Vector to move from.
     * @return Reference to this vector.
     * @post Steals resources from 'other', leaving it empty.
     */
    DynamicVector& operator=(DynamicVector&& other) noexcept;

    /**
     * @brief Destructor.
     * @post Frees allocated memory.
     */
    ~DynamicVector();

    // --- Modifiers ---

    /**
     * @brief Adds an element (copy version).
     * @param e Element to add.
     * @post Element is copied to end, resizes if needed.
     */
    void add(const TElem& e);

    /**
     * @brief Adds an element (move version).
     * @param e Element to add.
     * @post Element is moved to end, resizes if needed.
     */
    void add(TElem&& e);

    /**
     * @brief Removes first occurrence of an element.
     * @param e Element to remove.
     * @return true if element was found and removed, false otherwise.
     * @post Elements are shifted left if removal occurs.
     */
    bool remove(const TElem& e);

    // --- Capacity ---

    /**
     * @brief Gets current number of elements.
     * @return Number of elements in vector.
     */
    int size() const;

    /**
     * @brief Checks if vector is empty.
     * @return true if empty, false otherwise.
     */
    bool isEmpty() const;

    // --- Lookup ---

    /**
     * @brief Checks if element exists in vector.
     * @param e Element to search for.
     * @return true if found, false otherwise.
     */
    bool search(const TElem& e) const;

    // --- Element Access ---

    /**
     * @brief Accesses element at index (non-const version).
     * @param index Position to access.
     * @return Reference to the element.
     * @throws std::out_of_range if index is invalid.
     */
    TElem& operator[](int index);

    /**
     * @brief Accesses element at index (const version).
     * @param index Position to access.
     * @return Const reference to the element.
     * @throws std::out_of_range if index is invalid.
     */
    const TElem& operator[](int index) const;
};

// ================= Implementation ================= //

template <typename TElem>
DynamicVector<TElem>::DynamicVector()
    : nr_elem(0), capacity(5), arr(new TElem[5]) {
}

template <typename TElem>
DynamicVector<TElem>::DynamicVector(const DynamicVector& other)
    : nr_elem(other.nr_elem), capacity(other.capacity), arr(new TElem[other.capacity]) {
    for (int i = 0; i < nr_elem; i++)
        arr[i] = other.arr[i];
}

template <typename TElem>
DynamicVector<TElem>::DynamicVector(DynamicVector&& other) noexcept
    : nr_elem(other.nr_elem), capacity(other.capacity), arr(other.arr) {
    other.arr = nullptr;
    other.nr_elem = 0;
    other.capacity = 0;
}

template <typename TElem>
DynamicVector<TElem>& DynamicVector<TElem>::operator=(const DynamicVector& other) {
    if (this != &other) {
        TElem* newArr = new TElem[other.capacity];
        for (int i = 0; i < other.nr_elem; i++)
            newArr[i] = other.arr[i];

        delete[] arr;
        arr = newArr;
        nr_elem = other.nr_elem;
        capacity = other.capacity;
    }
    return *this;
}

template <typename TElem>
DynamicVector<TElem>& DynamicVector<TElem>::operator=(DynamicVector&& other) noexcept {
    if (this != &other) {
        delete[] arr;
        arr = other.arr;
        nr_elem = other.nr_elem;
        capacity = other.capacity;

        other.arr = nullptr;
        other.nr_elem = 0;
        other.capacity = 0;
    }
    return *this;
}

template <typename TElem>
DynamicVector<TElem>::~DynamicVector() {
    delete[] arr;
}

template <typename TElem>
void DynamicVector<TElem>::resize() {
    capacity *= 2;
    TElem* newArr = new TElem[capacity];
    for (int i = 0; i < nr_elem; i++)
        newArr[i] = std::move(arr[i]);

    delete[] arr;
    arr = newArr;
}

template <typename TElem>
void DynamicVector<TElem>::add(const TElem& e) {
    if (nr_elem == capacity)
        resize();
    arr[nr_elem++] = e;
}

template <typename TElem>
void DynamicVector<TElem>::add(TElem&& e) {
    if (nr_elem == capacity)
        resize();
    arr[nr_elem++] = std::move(e);
}

template <typename TElem>
bool DynamicVector<TElem>::remove(const TElem& e) {
    for (int i = 0; i < nr_elem; i++) {
        if (arr[i] == e) {
            for (int j = i; j < nr_elem - 1; j++)
                arr[j] = std::move(arr[j + 1]);
            nr_elem--;
            return true;
        }
    }
    return false;
}

template <typename TElem>
bool DynamicVector<TElem>::search(const TElem& e) const {
    for (int i = 0; i < nr_elem; i++) {
        if (arr[i] == e)
            return true;
    }
    return false;
}

template <typename TElem>
int DynamicVector<TElem>::size() const {
    return nr_elem;
}

template <typename TElem>
bool DynamicVector<TElem>::isEmpty() const {
    return nr_elem == 0;
}

template <typename TElem>
TElem& DynamicVector<TElem>::operator[](int index) {
    if (index < 0 || index >= nr_elem)
        throw std::out_of_range("Index out of bounds!");
    return arr[index];
}

template <typename TElem>
const TElem& DynamicVector<TElem>::operator[](int index) const {
    if (index < 0 || index >= nr_elem)
        throw std::out_of_range("Index out of bounds!");
    return arr[index];
}