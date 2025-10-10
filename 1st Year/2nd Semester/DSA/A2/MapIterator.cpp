#include "Map.h"
#include "MapIterator.h"
#include <exception>
using namespace std;


MapIterator::MapIterator(const Map& d) : map(d)
{
	currentNode = map.head;
}

//BC = WC = Theta(1)
void MapIterator::first() {
	currentNode = map.head;
}

//BC = WC = Theta(1)
void MapIterator::next() {
	if (!valid())
		throw exception();
	currentNode = currentNode->next;
}

//BC = WC = Theta(1)
TElem MapIterator::getCurrent(){
	if (!valid())
		throw exception();
	return currentNode->info;
}

//BC = WC = Theta(1)
bool MapIterator::valid() const {
	return currentNode !=nullptr;
}



