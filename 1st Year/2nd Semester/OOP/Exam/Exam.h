#pragma once

#include <QtWidgets/QWidget>
#include "ui_Exam.h"
#include "Observer.h"
#include "Repo.h"
class Exam : public QWidget, public Observer
{
    Q_OBJECT

public:
    Exam(Repo& repo, string name, string description, QWidget* parent = nullptr);
    ~Exam();
    void update() override;
    void populateListAssigned();
    void populateListUnassigned();
    void handleAddVolunteer();
private:
    Ui::ExamClass ui;
    Repo& repo;
    string name;
    string description;
};

