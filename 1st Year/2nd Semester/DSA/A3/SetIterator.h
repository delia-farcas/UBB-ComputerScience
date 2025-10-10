#pragma once
#include "Set.h"
#include <stack>

class SetIterator
{
	//DO NOT CHANGE THIS PART
	friend class Set;
private:
	//DO NOT CHANGE THIS PART
	const Set& set;
	SetIterator(const Set& s);

	int crtPos;
	std::stack<int> history;

public:
	void first();
	void next();
	TElem getCurrent();
	bool valid() const;
	void previous();
};


