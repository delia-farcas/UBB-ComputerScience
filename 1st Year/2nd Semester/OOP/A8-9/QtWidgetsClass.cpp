#include "QtWidgetsClass.h"
#include "Dogs_Model.h"

QtWidgetsClass::QtWidgetsClass(std::shared_ptr<UserRepository> repo, QWidget* parent)
    : QWidget(parent), userRepo(repo)
{
    QVBoxLayout* layout = new QVBoxLayout(this);

    // Create the model and connect it to the view
    model = new UserDogsModel(*userRepo, this);
    tableView = new QTableView(this);
    tableView->setModel(model);
    tableView->resizeColumnsToContents();

    layout->addWidget(tableView);

    QPushButton* backBtn = new QPushButton("Back");
    layout->addWidget(backBtn);
    connect(backBtn, &QPushButton::clicked, this, &QtWidgetsClass::backButtonClicked);
}
