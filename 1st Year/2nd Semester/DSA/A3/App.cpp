#include "Set.h"
#include "SetIterator.h"
#include "ExtendedTest.h"
#include "ShortTest.h"
#include <stack>
#include <iostream>
using namespace std;




int main() {

	testAll();
	cout << "Short test done!" << endl;
	testPrev();
	cout << "Test for the pref function done" << endl;
	testAllExtended();

	cout << "That's all!" << endl;
	system("pause");

}



