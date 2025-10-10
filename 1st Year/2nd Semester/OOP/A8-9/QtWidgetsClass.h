#pragma once
#include <QWidget>
#include <QTableView>
#include <QPushButton>
#include <QVBoxLayout>
#include "Dogs_Model.h"
#include "user_repository.h"

class QtWidgetsClass : public QWidget {
    Q_OBJECT

private:
    QTableView* tableView;
    UserDogsModel* model;
    std::shared_ptr<UserRepository> userRepo;

public:
    explicit QtWidgetsClass(std::shared_ptr<UserRepository> repo, QWidget* parent = nullptr);

signals:
    void backButtonClicked();
};
