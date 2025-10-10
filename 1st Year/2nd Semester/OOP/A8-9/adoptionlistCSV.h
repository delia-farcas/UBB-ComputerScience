#pragma once
#include "adoptionlist.h"

class AdoptionListCSV : public AdoptionList {
private:
	vector<Dog> elements;
	string filePath;
public:
	AdoptionListCSV(string filePath);
	void save(const Dog& dog) override;
	vector<Dog> getElements() override;
	void displayList() const override;
private:
	void writeToFile();
};

