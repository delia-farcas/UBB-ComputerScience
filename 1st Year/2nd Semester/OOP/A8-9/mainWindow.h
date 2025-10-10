#pragma once
#include <QMainWindow>
#include <QStackedWidget>
#include <QPushButton>
#include <QComboBox>
#include <QLabel>
#include <QVBoxLayout>
#include <QHBoxLayout>
#include <QMessageBox>
#include <QApplication>
#include <QFont>
#include "service.h"
#include "user_service.h"
#include "repository.h"
#include "adminwidget.h"
#include "userwidget.h"
#include "QtWidgetsClass.h"

class MainWindow : public QMainWindow
{
    Q_OBJECT
private slots:
    void clicked_adminButton();
    void clicked_userButton();
    void clicked_backToMain();
    void clicked_adoptionButton();

private:
    Repository repo;
    std::shared_ptr<UserRepository> userRepo;
    DogService service;
    UserService user_srv;
    QString FilePath;
    QString FileType;

    QStackedWidget* stackedWidget;
    QWidget* MainMenuWidget;
    QComboBox* fileTypeComboBox;
    AdminWidget* adminWidget;
    UserWidget* userWidget;
    QtWidgetsClass* adoptWidget;


    void setupMainWindow();
    
public:
    explicit MainWindow(QWidget* parent = nullptr);
    ~MainWindow();

};
