#include "SortedBag.h"
#include "SortedBagIterator.h"
#include <iostream>

using namespace std;
SortedBag::SortedBag(Relation r) {
	this->rel = r;
	this->nr_elem = 0;
	this->capacity = 5;
	this->elements = new TComp[this->capacity];
	this->freq = new int[this->capacity];
}

//BC: Theta(1), WC: Theta(n), Total: O(n)
void SortedBag::add(TComp e) {
    int pos = 0;
    bool found = false;
    while (pos < this->nr_elem && !found) {
        if (this->elements[pos] == e) {
            this->freq[pos]++;
            found = true;
        }
        else if (!this->rel(this->elements[pos], e)) {
            break;
        }
        pos++;
    }
    if (!found) {
        if (this->nr_elem == this->capacity) {
            this->capacity = 2 * this->capacity;
            TComp* newElements = new TComp[this->capacity];
            int* newFreq = new int[this->capacity];
            for (int i = 0; i < this->nr_elem; i++) {
                newElements[i] = this->elements[i];
                newFreq[i] = this->freq[i];
            }

            delete[] this->elements;
            delete[] this->freq;

            this->elements = newElements;
            this->freq = newFreq;
        }

        for (int i = nr_elem; i > pos; i--) {
            this->elements[i] = this->elements[i - 1];
            this->freq[i] = this->freq[i - 1];
        }
        this->elements[pos] = e;
        this->freq[pos] = 1;
        nr_elem++;
    }
}

//BC: Theta(1), WC: Theta(n), Total: O(n)
bool SortedBag::remove(TComp e) {
    int pos = -1;
    do {
        pos++;
    } while (pos < this->nr_elem && this->rel(this->elements[pos], e));
    if (pos > 0 && pos <= this->nr_elem && this->elements[pos - 1] == e) {
        this->freq[pos - 1]--;
        if (this->freq[pos - 1] == 0) {
            for (int i = pos - 1; i < nr_elem - 1; i++) {
                this->elements[i] = this->elements[i + 1];
                this->freq[i] = this->freq[i + 1];
            }
            nr_elem--;
        }
        return true;
    }
    return false;
}

//BC: Theta(1), WC: Theta(n), Total: O(n)
bool SortedBag::search(TComp elem) const {
    int pos = 0;
    while (pos < this->nr_elem && this->rel(this->elements[pos], elem)) {
        if (this->elements[pos] == elem) {
            return true;
        }
        pos++;
    }

    return false;
}

//BC: Theta(1), WC: Theta(n), Total: O(n)
int SortedBag::nrOccurrences(TComp elem) const {
    int pos = 0;
    while (pos < this->nr_elem && this->rel(this->elements[pos], elem)) {
        if (this->elements[pos] == elem) {
            return this->freq[pos];
        }
        pos++;
    }

    return 0;
}

//BC: Theta(n), WC: Theta(n), Total: Theta(n)
int SortedBag::size() const {
    int sum = 0;
    for (int i = 0; i < this->nr_elem; i++)
        sum += this->freq[i];
    return sum;
}

//BC: Theta(1), WC: Theta(1), Total: Theta(1)
bool SortedBag::isEmpty() const {
    if (this->nr_elem == 0)
        return true;
    return false;
}

//BC: Theta(1), WC: Theta(1), Total: Theta(1)
SortedBagIterator SortedBag::iterator() const {
    return SortedBagIterator(*this);
}

//BC:Theta(n), WC: Theta(n), Tota:O(n)
TComp SortedBag::mostFrequent() const {
    if (isEmpty())
        return NULL_TCOMP;
    int fr_max = -1, index = 0;
    for (int i = 0; i < this->nr_elem; i++)
        if (fr_max < this->freq[i]) {
            fr_max = this->freq[i];
            index = i;
        }
    return this->elements[index];
}

//BC: Theta(1), WC: Theta(1), Total: Theta(1)
SortedBag::~SortedBag() {
    delete[] this->elements;
    delete[] this->freq;
}
