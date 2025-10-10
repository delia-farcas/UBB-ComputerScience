#pragma once
#include "MultiMap.h"

class MultiMap;

class MultiMapIterator
{
	friend class MultiMap;

private:
	const MultiMap& col;
	// Current position in the hashtable
	int currentBucket;
	MultiMap::Node* currentNode;

	// Find the first non-empty bucket starting from currentBucket
	void findNextValidBucket();

	//DO NOT CHANGE THIS PART
	MultiMapIterator(const MultiMap& c);

public:
	TElem getCurrent() const;
	bool valid() const;
	void next();
	void first();
};
