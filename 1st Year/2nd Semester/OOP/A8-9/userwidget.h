#pragma once
#include <QWidget>
#include <QPushButton>
#include <QLabel>
#include <QLineEdit>
#include <QSpinBox>
#include <QTableWidget>
#include <QStackedWidget>
#include <vector>
#include <QVBoxLayout>
#include <QHBoxLayout>
#include <QGridLayout>
#include <QMessageBox>
#include <QHeaderView>
#include <QGroupBox>
#include "service.h"
#include "adoptionlistCSV.h"
#include "adoptionlistHTML.h"
#include "user_repository.h"

class UserWidget : public QWidget {
    Q_OBJECT
public:
    explicit UserWidget(DogService* service, std::shared_ptr<UserRepository> repo, QString& fileType, QString& fileName, QWidget* parent = nullptr);
    //void setFileType(const QString& fileType, const QString& filename);

signals:
    void backButtonClicked(); // Signal to notify MainWindow when back button is clicked

private:
    DogService* service;
    QString fileType;
    QString fileName;
    int currentDogIndex;
    std::vector<Dog> currentDogs;
    std::shared_ptr<UserRepository> adoptionRepo;
    AdoptionList* adoptionList;

    void setupUI();
    void connectSignalsAndSlots();
    void showDog(const Dog* dog);
    void clearDogDisplay();
    void updateDogView();

    QWidget* userWidget;
    QStackedWidget* stackedWidget;

    // Main menu page
    QWidget* menuPage;

    // Dog view page
    QWidget* dogViewPage;
    QLabel* dogNameLabel;
    QLabel* dogBreedLabel;
    QLabel* dogAgeLabel;
    QLabel* dogPhotoLabel;
    QPushButton* nextDogButton;
    QPushButton* adoptDogButton;
    QPushButton* backToDogMenuButton;

    // Filter page
    QWidget* filterPage;
    QLineEdit* breedFilterEdit;
    QSpinBox* ageFilterSpinBox;
    QPushButton* applyFilterButton;
    QPushButton* clearFilterButton;
    QPushButton* backToFilterMenuButton;

    // Adoption list page
    QWidget* adoptionListPage;
    QTableWidget* adoptionTable;
    QPushButton* backToAdoptionMenuButton;

    //BUTTONS
    // Menu buttons
    QPushButton* viewDogsButton;
    QPushButton* viewFilteredDogsButton;
    QPushButton* openAdoptionListButton;
    QPushButton* backButton;

private slots:
    void onViewDogsClicked();
    void onViewFilteredDogsClicked();
    void onSaveAdoptionListClicked();
    void onOpenAdoptionListClicked();
    void onBackClicked();
    void onNextDogClicked();
    void onAdoptDogClicked();
    void onApplyFilterClicked();
    void onClearFilterClicked();
};
