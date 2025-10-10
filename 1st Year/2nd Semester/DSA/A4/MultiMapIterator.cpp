#include "MultiMapIterator.h"
#include "MultiMap.h"
#include <exception>

//BC = WC = Theta(1)
MultiMapIterator::MultiMapIterator(const MultiMap& c) : col(c) {
	first();
}

//BC = Theta(1), WC = Theta(n), Total = O(n)
void MultiMapIterator::findNextValidBucket() {
	while (currentBucket < col.m && col.T[currentBucket] == nullptr) {
		currentBucket++;
	}
}

//BC = WC = Theta(1)
TElem MultiMapIterator::getCurrent() const {
	if (!valid()) {
		throw std::exception();
	}
	return currentNode->info;
}

//BC = WC = Theta(1)
bool MultiMapIterator::valid() const {
	return currentBucket < col.m && currentNode != nullptr;
}

//BC = Theta(1), WC = Theta(n), Total = O(n)
void MultiMapIterator::next() {
	if (!valid()) {
		throw std::exception();
	}

	currentNode = currentNode->next;

	if (currentNode == nullptr) {
		currentBucket++;
		findNextValidBucket();
		if (currentBucket < col.m) {
			currentNode = col.T[currentBucket];
		}
	}
}

//BC = Theta(1), WC = Theta(n), Total = O(n)
void MultiMapIterator::first() {
	currentBucket = 0;

	findNextValidBucket();

	if (currentBucket < col.m) {
		currentNode = col.T[currentBucket];
	}
	else {
		currentNode = nullptr;
	}
}
