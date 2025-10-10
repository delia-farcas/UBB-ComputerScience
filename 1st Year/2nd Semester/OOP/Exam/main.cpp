#include "Exam.h"
#include <QtWidgets/QApplication>
#include "Volunteeer.h"
#include <iostream>
#include <fstream>
#include <sstream>

int main(int argc, char *argv[])
{
    QApplication app(argc, argv);
    Repo repo;
    string line;
    ifstream file("departments.txt");
    if (!file.is_open()) {
        throw runtime_error("Failed to open file");
    }
    while (getline(file, line)) {
        istringstream iss(line);
        string name, description;

        if (getline(iss, name, '|') &&
            getline(iss, description)) {

            Exam* p = new Exam{ repo, name, description };
            repo.addObserver(p);
            p->show();
        }
    }
    return app.exec(); 
}
