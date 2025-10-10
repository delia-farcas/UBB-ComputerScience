#include "Repo.h"
#include <sstream>
#include <fstream>
#include <algorithm>
void Repo::loadFromFile() {
     ifstream file(filename);
     if (!file.is_open()) {
          throw runtime_error("Failed to open file: " + filename);
        }

        volunteers.clear();
        string line;

        while (getline(file, line)) {
            istringstream iss(line);
            string name, email, department, interestsStr;

            if (getline(iss, name, '|') &&
                getline(iss, email, '|') &&
                getline(iss, department, '|') &&
                getline(iss, interestsStr)) {

                vector<string> interests;
                istringstream interestsStream(interestsStr);
                string interest;

                while (getline(interestsStream, interest, ',')) {
                    if (!interest.empty()) {
                        interests.push_back(interest);
                    }
                }

                volunteers.emplace_back(name, email, interests, department);
            }
        }
        sort(this->volunteers.begin(), this->volunteers.end(), [](const Volunteeer& v1, const Volunteeer& v2) {
            return v1.getName() > v2.getName();
            });
        file.close();
    }

void Repo::saveToFile() {
        ofstream file("volunteers.txt");
        if (!file.is_open()) {
            throw runtime_error("Failed to open file for writing: volunteers.txt");
        }
        sort(this->volunteers.begin(), this->volunteers.end(), [](const Volunteeer& v1, const Volunteeer& v2) {
            return v1.getName() > v2.getName();
            });
        for (const auto& volunteer : volunteers) {
            file << volunteer.getName() << '|' << volunteer.getEmail() << '|' << volunteer.getDepartment()<< '|';

            vector<string>interests = volunteer.getInterests();
            for (size_t i = 0; i < interests.size(); ++i) {
                file << interests[i];
                if (i != interests.size() - 1) {
                    file << ',';
                }
            }

            file << '\n';
        }

        file.close();
    }


void Repo::addVolunteer(string& name, string& email, vector<string> interests) {
    Volunteeer::validate_volunteer(name, email);

    string department;
    Volunteeer v(name, email, interests, department);
    volunteers.push_back(v);
    saveToFile();
    notify();
}


const vector<Volunteeer>& Repo::getAll() const {
    return volunteers;
}