#include <iostream>

#include "ShortTest.h"
#include "ExtendedTest.h"

int main(){
    testAll();
    testAllExtended();
    std::cout<<"Finished IL Tests!"<<std::endl;
    testRemoveAll();
    std::cout << "Additional function is ok" << std::endl;
	system("pause");
}