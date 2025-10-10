#include <iostream>
#include "MultiMap.h"
#include "ExtendedTest.h"
#include "ShortTest.h"
#include "MultiMapIterator.h"

using namespace std;


int main() {


	testAll();
	cout << "Short tests done!" << endl;
	testValueRange();
	cout << "ADDITIONAL FUNCTION IS OK" << endl;
	testAllExtended();
	cout << "End" << endl;
	system("pause");

}
