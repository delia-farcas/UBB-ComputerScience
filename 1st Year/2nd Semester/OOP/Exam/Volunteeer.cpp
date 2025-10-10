#include "Volunteeer.h"
#include <stdexcept>

string Volunteeer::getName() const {
	return this->name;
}


string Volunteeer::getEmail() const {
	return this->email;
}

string Volunteeer::getDepartment() const {
	return this->department;
}

vector<string> Volunteeer::getInterests() const {
	return this->interests;
}

void Volunteeer::validate_volunteer(const string& name, const string& email) {
	if (name.empty())
		throw invalid_argument("Name is empty");
	if (email.empty())
		throw invalid_argument("Email is empty");
}

string Volunteeer::toStr() {
	return "~Volunteer: " + this->name + " | email: " + this->email + "\n";
}