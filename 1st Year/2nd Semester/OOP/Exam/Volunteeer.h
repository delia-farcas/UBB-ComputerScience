#pragma once
#include <string>
#include <vector>
using namespace std;

class Volunteeer
{
private:
	string name;
	string email;
	vector<string> interests;
	string department;
public:
	Volunteeer(string& name, string& email, vector<string>& interests, string& department) : name(name), email(email), interests(interests), department(department) {}
	string getName() const;
	string getEmail() const;
	string getDepartment() const;
	vector<string> getInterests() const;
	static void validate_volunteer(const string& name, const string& email);
	string toStr();
};

