#include "SetIterator.h"
#include "Set.h"
#include <exception>


SetIterator::SetIterator(const Set& m) : set(m)
{
	this->crtPos = this->set.list.head;
}

// BC = Theta(1), WC = Theta(1), Total = Theta(1)
void SetIterator::first() {
	while (!history.empty()) history.pop();
	this->crtPos = this->set.list.head;
}

// BC = Theta(1), WC = Theta(1), Total = Theta(1)
void SetIterator::next() {
	if (!this->valid()) {
		throw std::exception();
	}
	history.push(crtPos);
	this->crtPos = set.list.next[crtPos];
}

// BC = Theta(1), WC = Theta(1), Total = Theta(1)
TElem SetIterator::getCurrent()
{
	if (!this->valid()) {
		throw std::exception();  
	}
	return this->set.list.elems[this->crtPos];
}

// BC = Theta(1), WC = Theta(1), Total = Theta(1)
bool SetIterator::valid() const {
	return (crtPos != -1);
}

//BC = Theta(1), WC = Theta(1), Total = Theta(1)
void SetIterator::previous() {
	if (history.empty()) {
		throw std::exception();
	}
	this->crtPos = history.top();
	history.pop();
}

