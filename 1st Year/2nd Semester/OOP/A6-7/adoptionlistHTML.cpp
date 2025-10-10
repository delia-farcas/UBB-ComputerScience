#include "adoptionlistHTML.h"
#include <fstream>
#include <cstdlib>

AdoptionListHTML::AdoptionListHTML(string filePath) : filePath(filePath) {}

void AdoptionListHTML::save(const Dog& dog) {
    this->elements.push_back(dog);
    this->writeToFile();
}

std::vector<Dog> AdoptionListHTML::getElements() {
    return this->elements;
}

void AdoptionListHTML::writeToFile() {
    ofstream fout(this->filePath);
    if (fout.is_open() == false)
        throw exception("File not open!");

    fout << "<!DOCTYPE html>\n";
    fout << "<html>\n";
    fout << "<head>\n";
    fout << "    <title>Dog Adoption List</title>\n";
    fout << "    <style>\n";
    fout << "        table { border-collapse: collapse; width: 100%; }\n";
    fout << "        th, td { border: 1px solid #ddd; padding: 8px; text-align: left; }\n";
    fout << "        th { background-color: #f2f2f2; }\n";
    fout << "        tr:nth-child(even) { background-color: #f9f9f9; }\n";
    fout << "    </style>\n";
    fout << "</head>\n";
    fout << "<body>\n";
    fout << "    <h1>Dog Adoption List</h1>\n";
    fout << "    <table>\n";
    fout << "        <tr>\n";
    fout << "            <th>Name</th>\n";
    fout << "            <th>Breed</th>\n";
    fout << "            <th>Age</th>\n";
    fout << "            <th>Photograph</th>\n";
    fout << "        </tr>\n";


    for (int i = 0; i < this->elements.size(); i++) {
        fout << "        <tr>\n";
        fout << "            <td>" << this->elements[i].getName() << "</td>\n";
        fout << "            <td>" << this->elements[i].getBreed() << "</td>\n";
        fout << "            <td>" << this->elements[i].getAge() << "</td>\n";
        fout << "            <td>" << this->elements[i].getPhotograph() << "</td>\n";
        fout << "        </tr>\n";
    }


    fout << "    </table>\n";
    fout << "</body>\n";
    fout << "</html>\n";

    fout.close();
}

void AdoptionListHTML::displayList() const {
    // Open HTML file with default browser
#ifdef _WIN32
    string command = "start " + filePath;
#elif __APPLE__
    string command = "open " + filePath;
#else
    string command = "xdg-open " + filePath;
#endif

    system(command.c_str());
}
