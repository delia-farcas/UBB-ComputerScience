#pragma once
#include "adoptionlist.h"

class AdoptionListHTML : public AdoptionList {
private:
	vector<Dog> elements;
	string filePath;
public:
	AdoptionListHTML(string filePath);
	void save(const Dog& dog) override;
	vector<Dog> getElements() override;
	void displayList() const override;
private:
	void writeToFile();
};

