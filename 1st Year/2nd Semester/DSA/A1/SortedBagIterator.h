#pragma once
#include "SortedBag.h"

class SortedBag;

class SortedBagIterator
{
	friend class SortedBag;

private:
	const SortedBag& bag;
	int crtPosition;
	int crtFreq;
	SortedBagIterator(const SortedBag& b);


public:
	TComp getCurrent();
	bool valid();
	void next();
	void first();
};

