#include "Set.h"
#include "SetITerator.h"


//BC = WC = Theta(n)
Set::Set() {
	this->list.cap = 5;
	this->list.elems = new TElem[list.cap];
	this->list.next = new int[list.cap];
	this->list.head = -1;
	for (int i = 0; i < list.cap - 1; i++)
		this->list.next[i] = i + 1;
	this->list.next[list.cap-1] = -1;
	this->list.firstEmpty = 0;
	this->crtSize = 0;
}

//BC = Theta(1), WC = Theta(n), Total = O(n)
bool Set::add(TElem elem) {
	if (search(elem) == true)
		return false;
	if (this->list.firstEmpty == -1) {
		TElem* newElements = new TElem[this->list.cap * 2];
		int* newNext = new int[this->list.cap * 2];
		for (int i = 0; i < this->list.cap; i++) {
			newElements[i] = this->list.elems[i];
			newNext[i] = this->list.next[i];
		}
		for (int i = this->list.cap; i < this->list.cap * 2; i++)
			newNext[i] = i + 1;
		newNext[this->list.cap * 2 - 1] = -1;
		delete[] this->list.elems;
		delete[] this->list.next;
		this->list.elems = newElements;
		this->list.next = newNext;
		this->list.firstEmpty = this->list.cap;
		this->list.cap = this->list.cap * 2;
	}
	int newPos = this->list.firstEmpty;
	this->list.elems[newPos] = elem;
	this->list.firstEmpty = this->list.next[list.firstEmpty];
	this->list.next[newPos] = this->list.head;
	this->list.head = newPos;                
	this->crtSize++;
	return true;
}


//BC = Theta(1), WC = Theta(n), Total = O(n)
bool Set::remove(TElem elem) {
	int crtNode = this->list.head;
	int prevNode = -1;
	while (crtNode != -1 && this->list.elems[crtNode] != elem) {
		prevNode = crtNode;
		crtNode = this->list.next[crtNode];
	}
	if (crtNode != -1){
		if (crtNode == this->list.head)
			this->list.head = this->list.next[this->list.head];
		else
			this->list.next[prevNode] = this->list.next[crtNode];
		this->list.next[crtNode] = this->list.firstEmpty;
		this->list.firstEmpty = crtNode;
	}
	else
		return false;
	this->crtSize--;
	return true;
}

//BC = Theta(1), WC = Theta(n), Total = O(n)
bool Set::search(TElem elem) const {
	int crt = this->list.head;
	while (crt != -1 && this->list.elems[crt] != elem) {
		crt = this->list.next[crt];
	}
	if (crt != -1)
		return true;
	return false;
}

//BC = Theta(1), WC = Theta(1), Total = Theta(1)
int Set::size() const {
	return this->crtSize;
}

//BC = Theta(1), WC = Theta(1), Total = Theta(1)
bool Set::isEmpty() const {
	return this->crtSize == 0;
}

// BC = Theta(1), WC = Theta(1), Total = Theta(1)
Set::~Set() {
	delete[] list.elems;
	delete[] list.next;
}

// BC = Theta(1), WC = Theta(1), Total = Theta(1)
SetIterator Set::iterator() const {
	return SetIterator(*this);
}


