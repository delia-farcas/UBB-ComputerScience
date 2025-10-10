#include "Map.h"
#include "MapIterator.h"
#include<iostream>
using namespace std;

Map::Map() {
	head = nullptr;
	count = 0;
}

//BC = WC = Theta(n)
Map::~Map() {
	Node* current = head;
	while (current != nullptr) {
		Node* next = current->next;
		delete[] current;
		current = next;
	}
}
	
//BC: Theta(1), WC: Theta(n), Total:O(n)
TValue Map::add(TKey c, TValue v) {
	Node* current = head;
	Node* prev = nullptr;

	while (current != nullptr && current->info.first != c) {
		prev = current;
		current = current->next;
	}

	if (current != nullptr) {
		TValue oldValue = current->info.second;
		current->info.second = v;
		return oldValue;
	}

	Node* newNode = new Node(c, v);

	if (prev == nullptr) {
		newNode->next = head;
		head = newNode;
	}
	else {
		newNode->next = current;
		prev->next = newNode;
	}

	count++;
	return NULL_TVALUE;
}

//BC: Theta(1), WC: Theta(n), Total: O(n)
TValue Map::search(TKey c) const{
	Node* current = head;

	while (current != nullptr) {
		if (current->info.first == c)
			return current->info.second;
		current = current->next;
	}

	return NULL_TVALUE;
}

//BC: Theta(1), WC: Theta(n), Total: O(n)
TValue Map::remove(TKey c){
	Node* current = head;
	Node* prev = nullptr;

	while (current != nullptr && current->info.first != c) {
		prev = current;
		current = current->next;
	}

	if (current == nullptr) {
		return NULL_TVALUE;
	}

	TValue oldValue = current->info.second;
	
	if (prev == nullptr)//if the value is the head
		head = current->next;
	else
		prev->next = current->next;

	delete[] current;
	count--;

	return oldValue;
}

//BC = WC = Theta(1)
int Map::size() const {
	return count;
}

//BC = WC = Theta(1)
bool Map::isEmpty() const{
	return count == 0;
}

//BC = theta(1); WC = Theta(n); Total = O(n)
TKey Map::minKey() const {
	if (isEmpty())
		return NULL_TKEY;
	int min = INT_MAX;
	Node* current = head;
	Node* prev = nullptr;

	while (current != nullptr) {
		if (current->info.first < min)
			min = current->info.first;
		prev = current;
		current = current->next;
	}
	return min;
}

//BC = WC = Theta(1)
MapIterator Map::iterator() const {
	return MapIterator(*this);
}



