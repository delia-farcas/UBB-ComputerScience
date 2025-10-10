#include "Exam.h"
#include <QString>
#include<QMessageBox>
Exam::Exam(Repo& repo, string n, string d, QWidget* parent)
    :  repo(repo), name(n), description(d), QWidget(parent)
{
    ui.setupUi(this);
    ui.label_name->setText(QString::fromStdString(name));
    ui.label_description->setText(QString::fromStdString(description));
    populateListAssigned();
    populateListUnassigned();
    connect(ui.pushButton, &QPushButton::clicked, this, &Exam::handleAddVolunteer);

}

Exam::~Exam()
{}

void Exam::update()
{
    populateListAssigned();
    populateListUnassigned();
}

void Exam::populateListAssigned() {
    vector<Volunteeer> vol = repo.getAll();
    ui.listWidget_assigned->clear();

    for (auto volunteer : vol)
    {
        if (volunteer.getDepartment() == name) {
            string s = volunteer.toStr();
            QListWidgetItem* item = new QListWidgetItem{ QString::fromStdString(s) };
            ui.listWidget_assigned->addItem(item);
        }
    }
}

void Exam::populateListUnassigned() {
    vector<Volunteeer> vol = repo.getAll();
    ui.listWidget->clear();

    for (auto volunteer : vol)
    {
        if (volunteer.getDepartment() == " " || volunteer.getDepartment().empty()) {
            string s = volunteer.toStr();
            QListWidgetItem* item = new QListWidgetItem{ QString::fromStdString(s) };
            ui.listWidget->addItem(item);
        }
    }
}

void Exam::handleAddVolunteer() {
    QString name = ui.nameInput->text().trimmed();
    QString email = ui.emailInput->text().trimmed();
    QString interestsStr = ui.interestsInput->text().trimmed();

    if (name.isEmpty() || email.isEmpty()) {
        QMessageBox::warning(this, "Validation Error", "Name and Email must not be empty.");
        return;
    }

    std::string stdName = name.toStdString();
    std::string stdEmail = email.toStdString();
    std::vector<std::string> interests;

    QStringList interestList = interestsStr.split(',', Qt::SkipEmptyParts);
    for (const QString& interest : interestList) {
        interests.push_back(interest.trimmed().toStdString());
    }

    try {
        repo.addVolunteer(stdName, stdEmail, interests);
        ui.nameInput->clear();
        ui.emailInput->clear();
        ui.interestsInput->clear();
    }
    catch (const std::exception& ex) {
        QMessageBox::critical(this, "Error", QString::fromStdString(ex.what()));
    }
    update();
}
