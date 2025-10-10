#include "SortedBagIterator.h"
#include "SortedBag.h"
#include <exception>

using namespace std;

SortedBagIterator::SortedBagIterator(const SortedBag& b) : bag(b) {
	this->crtPosition = 0;
	this->crtFreq = 1;
}

//BC: Theta(1), WC: Theta(1), Total: Theta(1)
TComp SortedBagIterator::getCurrent() {
    if (!this->valid()) {
        throw exception();
    }
    return this->bag.elements[crtPosition];
}

//BC: Theta(1), WC: Theta(1), Total: Theta(1)
bool SortedBagIterator::valid() {
    return this->crtPosition < this->bag.nr_elem;
    return false;  // This line is unreachable and should be removed
}

//BC: Theta(1), WC: Theta(1), Total: Theta(1)
void SortedBagIterator::next() {
    if (!this->valid()) {
        throw exception();
    }
    this->crtFreq++;
    if (this->crtFreq > this->bag.freq[this->crtPosition]) {
        this->crtPosition++;
        this->crtFreq = 1;
    }
}

//BC: Theta(1), WC: Theta(1), Total: Theta(1)
void SortedBagIterator::first() {
    this->crtPosition = 0;
    this->crtFreq = 1;
}

