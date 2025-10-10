#pragma once
#include <QWidget>
#include <QTableWidget>
#include <QLineEdit>
#include <QSpinBox>
#include <QPushButton>
#include <QVBoxLayout>
#include <QHBoxLayout>
#include <QGridLayout>
#include <QLabel>
#include <QGroupBox>
#include <QHeaderView>
#include <QMessageBox>
#include <QShortcut>
#include "service.h"
#include "commandmanager.h"

class AdminWidget : public QWidget
{
    Q_OBJECT

public:
    explicit AdminWidget(DogService* service, QWidget* parent = nullptr);
    void refreshTable(); // Public method for commands to refresh the table

signals:
    void backButtonClicked();

private slots:
    void onDogSelected(int row, int column);
    void onAddDog();
    void onRemoveDog();
    void onUpdateDog();
    void onUndo();
    void onRedo();

private:
    void setupUI();
    void populateTable();
    void clearForm();
    void showMessage(const QString& message);
    void updateUndoRedoButtons();

    DogService* service;
    CommandManager commandManager;

    // UI Components
    QTableWidget* dogsTable;
    QLineEdit* idLineEdit;
    QLineEdit* nameLineEdit;
    QLineEdit* breedLineEdit;
    QSpinBox* ageSpinBox;
    QLineEdit* photographLineEdit;

    QPushButton* addButton;
    QPushButton* removeButton;
    QPushButton* updateButton;
    QPushButton* undoButton;
    QPushButton* redoButton;
    QPushButton* backButton;

    // Keyboard shortcuts
    QShortcut* undoShortcut;
    QShortcut* redoShortcut;
};