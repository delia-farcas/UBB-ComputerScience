#include "MultiMap.h"
#include "MultiMapIterator.h"
#include <exception>
#include <iostream>

using namespace std;

MultiMap::MultiMap() {
	m = 101;
	T = new Node * [m];
	for (int i = 0; i < m; i++) {
		T[i] = nullptr;
	}
	count = 0;
}

//BC = WC = Theta(1)
void MultiMap::add(TKey c, TValue v) {
	int position = h(c);

	Node* newNode = new Node(c, v);

	newNode->next = T[position];
	T[position] = newNode;

	count++;
}

//BC = Theta(1), WC = Theta(n), Total = O(n)
bool MultiMap::remove(TKey c, TValue v) {
	int position = h(c);

	if (T[position] == nullptr) {
		return false;
	}

	if (T[position]->info.first == c && T[position]->info.second == v) {
		Node* nodeToDelete = T[position];
		T[position] = T[position]->next;
		delete nodeToDelete;
		count--;
		return true;
	}

	Node* current = T[position];
	Node* prev = current;
	while (current != nullptr) {
		if (current->info.first == c && current->info.second == v) {
			prev->next = current->next;
			delete current;
			count--;
			return true;
		}
		prev = current;
		current = current->next;

	}
	return false;
}

//BC = WC = Theta(n)
vector<TValue> MultiMap::search(TKey c) const {
	vector<TValue> values;

	int position = h(c);

	Node* currentNode = T[position];

	while (currentNode != nullptr) {
		if (currentNode->info.first == c) {
			values.push_back(currentNode->info.second);
		}
		currentNode = currentNode->next;
	}

	return values;
}

//BC = WC = Theta(1)
int MultiMap::size() const {
	return count;
}

//BC = WC = Theta(1)
bool MultiMap::isEmpty() const {
	return count == 0;
}

//BC = WC = Theta(1)
MultiMapIterator MultiMap::iterator() const {
	return MultiMapIterator(*this);
}

//BC = WC = Theta(n)
int MultiMap::getValueRange() const {
	MultiMapIterator iter = this->iterator();
	if (this->isEmpty())
		return -1;
	int max = -111111, min = 111111;
	while (iter.valid()) {
		int current_elem = iter.getCurrent().second;
		if (current_elem > max) {
			max = current_elem;
		}
		if (current_elem < min) {
			min = current_elem;
		}
		iter.next();
	}
	return max - min;
}

//BC = WC = Theta(n)
MultiMap::~MultiMap() {
	for (int i = 0; i < m; i++) {
		Node* current = T[i];
		while (current != nullptr) {
			Node* next = current->next;
			delete current;
			current = next;
		}
	}
	delete[] T;
}
