#pragma once
#include <vector>
#include <string>
#include "Volunteeer.h"
#include "Observer.h"
using namespace std;
class Repo : public Subiect
{
private:
	string& filename;
	vector<Volunteeer> volunteers;
	void loadFromFile();
public:
	Repo(string filename = "Volunteers.txt") : filename(filename) {
		loadFromFile();
	}
	void saveToFile();
	void addVolunteer(string& name, string& email, vector<string> interests);
	const vector<Volunteeer>& getAll() const;

};

