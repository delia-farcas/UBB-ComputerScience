#pragma once
#include "SortedIndexedList.h"

//DO NOT CHANGE THIS PART
class ListIterator {
	friend class SortedIndexedList;
private:
	const SortedIndexedList& list;
	ListIterator(const SortedIndexedList& list);

	BSTNode* currentNode;

	// Helper methods for navigation
	BSTNode* findLeftmost(BSTNode* node);
	BSTNode* findSuccessor(BSTNode* node);

public:
	void first();
	void next();
	bool valid() const;
	TComp getCurrent() const;
};