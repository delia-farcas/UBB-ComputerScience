#include "ExtendedTest.h"
#include "ShortTest.h"

#include "Map.h"


#include <iostream>
using namespace std;


int main() {
	testAll();
	testAllExtended();

	cout << "That's all!" << endl;
	test_minKey();
	system("pause");
	return 0;
}


