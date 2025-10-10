#include "adoptionlistCSV.h"
#include <fstream>
#include <cstdlib>

AdoptionListCSV::AdoptionListCSV(string filePath) : filePath(filePath) {}

void AdoptionListCSV::save(const Dog& dog) {
	this->elements.push_back(dog);
	this->writeToFile();
}

std::vector<Dog> AdoptionListCSV::getElements() {
	return this->elements;
}

void AdoptionListCSV::writeToFile() {
	ofstream fout(this->filePath);
	if (fout.is_open() == false)
		throw exception("File not open!");
	for (int i = 0; i < this->elements.size(); i++)
	{
		fout << this->elements[i] << "\n";
	}
	fout.close();
}

void AdoptionListCSV::displayList() const {
	// Open CSV file with default application (notepad on Windows)
#ifdef _WIN32
	string command = "start " + filePath;
#elif __APPLE__
	string command = "open " + filePath;
#else
	string command = "xdg-open " + filePath;
#endif

	system(command.c_str());
}
