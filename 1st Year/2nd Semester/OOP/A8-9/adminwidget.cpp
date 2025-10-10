#include "adminwidget.h"
#include "dogcommands.h"
#include <QFont>
#include <QKeySequence>

AdminWidget::AdminWidget(DogService* service, QWidget* parent)
    : QWidget(parent), service(service)
{
    setupUI();
    populateTable();
    updateUndoRedoButtons();
}

void AdminWidget::setupUI() {
    QVBoxLayout* mainLayout = new QVBoxLayout(this);

    QLabel* titleLabel = new QLabel("Administrator Mode");
    QFont titleFont = titleLabel->font();
    titleFont.setPointSize(16);
    titleFont.setBold(true);
    titleLabel->setFont(titleFont);
    titleLabel->setAlignment(Qt::AlignCenter);
    mainLayout->addWidget(titleLabel);

    dogsTable = new QTableWidget();
    dogsTable->setColumnCount(5);
    dogsTable->setHorizontalHeaderLabels({ "ID", "Name", "Breed", "Age", "Photograph" });
    dogsTable->horizontalHeader()->setSectionResizeMode(QHeaderView::Stretch);
    dogsTable->setSelectionBehavior(QAbstractItemView::SelectRows);
    dogsTable->setEditTriggers(QAbstractItemView::NoEditTriggers);
    mainLayout->addWidget(dogsTable);

    QGroupBox* formGroup = new QGroupBox("Dog Details");
    QGridLayout* formLayout = new QGridLayout(formGroup);

    formLayout->addWidget(new QLabel("ID:"), 0, 0);
    idLineEdit = new QLineEdit();
    idLineEdit->setReadOnly(true);
    formLayout->addWidget(idLineEdit, 0, 1);

    formLayout->addWidget(new QLabel("Name:"), 1, 0);
    nameLineEdit = new QLineEdit();
    formLayout->addWidget(nameLineEdit, 1, 1);

    formLayout->addWidget(new QLabel("Breed:"), 2, 0);
    breedLineEdit = new QLineEdit();
    formLayout->addWidget(breedLineEdit, 2, 1);

    formLayout->addWidget(new QLabel("Age:"), 3, 0);
    ageSpinBox = new QSpinBox();
    ageSpinBox->setRange(0, 20);
    formLayout->addWidget(ageSpinBox, 3, 1);

    formLayout->addWidget(new QLabel("Photograph URL:"), 4, 0);
    photographLineEdit = new QLineEdit();
    formLayout->addWidget(photographLineEdit, 4, 1);

    mainLayout->addWidget(formGroup);

    // Main action buttons
    QHBoxLayout* buttonLayout = new QHBoxLayout();

    addButton = new QPushButton("Add Dog");
    removeButton = new QPushButton("Remove Dog");
    updateButton = new QPushButton("Update Dog");

    buttonLayout->addWidget(addButton);
    buttonLayout->addWidget(removeButton);
    buttonLayout->addWidget(updateButton);

    mainLayout->addLayout(buttonLayout);

    // Undo/Redo buttons
    QHBoxLayout* undoRedoLayout = new QHBoxLayout();

    undoButton = new QPushButton("Undo (Ctrl+Z)");
    redoButton = new QPushButton("Redo (Ctrl+Y)");

    undoRedoLayout->addWidget(undoButton);
    undoRedoLayout->addWidget(redoButton);
    undoRedoLayout->addStretch(); // Add stretch to push buttons to the left

    mainLayout->addLayout(undoRedoLayout);

    backButton = new QPushButton("Back to Main Menu");
    mainLayout->addWidget(backButton);

    // Connect signals
    connect(dogsTable, &QTableWidget::cellClicked, this, &AdminWidget::onDogSelected);
    connect(addButton, &QPushButton::clicked, this, &AdminWidget::onAddDog);
    connect(removeButton, &QPushButton::clicked, this, &AdminWidget::onRemoveDog);
    connect(updateButton, &QPushButton::clicked, this, &AdminWidget::onUpdateDog);
    connect(undoButton, &QPushButton::clicked, this, &AdminWidget::onUndo);
    connect(redoButton, &QPushButton::clicked, this, &AdminWidget::onRedo);
    connect(backButton, &QPushButton::clicked, this, &AdminWidget::backButtonClicked);

    // Setup keyboard shortcuts
    undoShortcut = new QShortcut(QKeySequence::Undo, this);
    redoShortcut = new QShortcut(QKeySequence::Redo, this);

    connect(undoShortcut, &QShortcut::activated, this, &AdminWidget::onUndo);
    connect(redoShortcut, &QShortcut::activated, this, &AdminWidget::onRedo);
}

void AdminWidget::populateTable() {
    dogsTable->setRowCount(0);

    const std::vector<Dog>& dogs = service->getAllDogs();

    for (const auto& dog : dogs) {
        int row = dogsTable->rowCount();
        dogsTable->insertRow(row);

        dogsTable->setItem(row, 0, new QTableWidgetItem(QString::number(dog.getId())));
        dogsTable->setItem(row, 1, new QTableWidgetItem(QString::fromStdString(dog.getName())));
        dogsTable->setItem(row, 2, new QTableWidgetItem(QString::fromStdString(dog.getBreed())));
        dogsTable->setItem(row, 3, new QTableWidgetItem(QString::number(dog.getAge())));
        dogsTable->setItem(row, 4, new QTableWidgetItem(QString::fromStdString(dog.getPhotograph())));
    }
}

void AdminWidget::refreshTable() {
    populateTable();
    clearForm();
    updateUndoRedoButtons();
}

void AdminWidget::onDogSelected(int row, int column) {
    Q_UNUSED(column);

    idLineEdit->setText(dogsTable->item(row, 0)->text());
    nameLineEdit->setText(dogsTable->item(row, 1)->text());
    breedLineEdit->setText(dogsTable->item(row, 2)->text());
    ageSpinBox->setValue(dogsTable->item(row, 3)->text().toInt());
    photographLineEdit->setText(dogsTable->item(row, 4)->text());
}

void AdminWidget::onAddDog() {
    try {
        auto command = std::make_unique<AddDogCommand>(
            service, this,
            nameLineEdit->text().toStdString(),
            breedLineEdit->text().toStdString(),
            ageSpinBox->value(),
            photographLineEdit->text().toStdString()
        );

        commandManager.executeCommand(std::move(command));
        clearForm();
        updateUndoRedoButtons();
        showMessage("Dog added successfully!");
    }
    catch (const std::exception& e) {
        showMessage(QString("Error: ") + e.what());
    }
}

void AdminWidget::onRemoveDog() {
    if (idLineEdit->text().isEmpty()) {
        showMessage("Please select a dog to remove");
        return;
    }

    try {
        int id = idLineEdit->text().toInt();
        auto command = std::make_unique<RemoveDogCommand>(service, this, id);

        commandManager.executeCommand(std::move(command));
        clearForm();
        updateUndoRedoButtons();
        showMessage("Dog removed successfully!");
    }
    catch (const std::exception& e) {
        showMessage(QString("Error: ") + e.what());
    }
}

void AdminWidget::onUpdateDog() {
    if (idLineEdit->text().isEmpty()) {
        showMessage("Please select a dog to update");
        return;
    }

    try {
        auto command = std::make_unique<UpdateDogCommand>(
            service, this,
            idLineEdit->text().toInt(),
            nameLineEdit->text().toStdString(),
            breedLineEdit->text().toStdString(),
            ageSpinBox->value(),
            photographLineEdit->text().toStdString()
        );

        commandManager.executeCommand(std::move(command));
        updateUndoRedoButtons();
        showMessage("Dog updated successfully!");
    }
    catch (const std::exception& e) {
        showMessage(QString("Error: ") + e.what());
    }
}

void AdminWidget::onUndo() {
    try {
        if (commandManager.canUndo()) {
            commandManager.undo();
            updateUndoRedoButtons();
            showMessage("Operation undone successfully!");
        }
    }
    catch (const std::exception& e) {
        showMessage(QString("Undo failed: ") + e.what());
    }
}

void AdminWidget::onRedo() {
    try {
        if (commandManager.canRedo()) {
            commandManager.redo();
            updateUndoRedoButtons();
            showMessage("Operation redone successfully!");
        }
    }
    catch (const std::exception& e) {
        showMessage(QString("Redo failed: ") + e.what());
    }
}

void AdminWidget::updateUndoRedoButtons() {
    undoButton->setEnabled(commandManager.canUndo());
    redoButton->setEnabled(commandManager.canRedo());
}

void AdminWidget::clearForm() {
    idLineEdit->clear();
    nameLineEdit->clear();
    breedLineEdit->clear();
    ageSpinBox->setValue(0);
    photographLineEdit->clear();
}

void AdminWidget::showMessage(const QString& message) {
    QMessageBox::information(this, "Information", message);
}
