#include "ShortTest.h"
#include <assert.h>
#include "Set.h"
#include "SetIterator.h"
#include <iostream>

void testAll() { 
	Set s;
	assert(s.isEmpty() == true);
	assert(s.size() == 0); 
	assert(s.add(5)==true);
	assert(s.add(1)==true);
	assert(s.add(10)==true);
	assert(s.add(7)==true);
	assert(s.add(1) == false);
	assert(s.add(10)==false);
	assert(s.add(-3)==true);
	assert(s.size() == 5);
	assert(s.search(10) == true);
	assert(s.search(16) == false);
	assert(s.remove(1) == true);
	assert(s.remove(6) == false);
	assert(s.size() == 4);
	
	SetIterator it = s.iterator();
	it.first();
	int sum = 0;
	while (it.valid()) {
		TElem e = it.getCurrent();
		sum += e;
		it.next();
	}
	assert(sum == 19);

}

void testPrev() {
	Set s;
	s.add(5);
	s.add(4);
	s.add(3);
	s.add(2);

	SetIterator it = s.iterator();
	it.first(); //2      
	it.next();  //3     
	it.next();  //4     

	it.previous(); //3   
	TElem e = it.getCurrent();
	assert(e == 3);

	it.previous(); //2 
	e = it.getCurrent();
	assert(e == 2);

}