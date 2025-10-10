#include "userwidget.h"
#include <QFileDialog>
#include <QPixmap>
#include <QFormLayout>
#include <QDesktopServices>
#include <QUrl>
UserWidget::UserWidget(DogService* service, std::shared_ptr<UserRepository> repo, QString& fileType, QString& fileName, QWidget* parent) :
    service(service), adoptionRepo(repo), fileType(fileType), fileName(fileName), QWidget(parent), currentDogIndex(0) {
    setWindowTitle("Dog shelter application: user mode");

    // Initialize the appropriate adoption list based on file type
    if (fileType.toLower() == "csv") {
        adoptionList = new AdoptionListCSV(fileName.toStdString());
    }
    else if (fileType.toLower() == "html") {
        adoptionList = new AdoptionListHTML(fileName.toStdString());
    }
    else {
        // Default to CSV if type is not recognized
        adoptionList = new AdoptionListCSV(fileName.toStdString());
    }

    setupUI();
    connectSignalsAndSlots();
}

void UserWidget::setupUI() {
    // Main layout
    QVBoxLayout* mainLayout = new QVBoxLayout(this);
    mainLayout->setSpacing(10);
    mainLayout->setContentsMargins(30, 25, 25, 25);

    // Create stacked widget for different pages
    stackedWidget = new QStackedWidget();

    // ===== MENU PAGE =====
    menuPage = new QWidget();
    QVBoxLayout* menuLayout = new QVBoxLayout(menuPage);
    menuLayout->setSpacing(10);

    QLabel* titleLabel = new QLabel("True Tails Rescue dog shelter");
    QFont titleFont("Delius", 19, QFont::Medium);
    titleLabel->setFont(titleFont);
    titleLabel->setAlignment(Qt::AlignCenter);
    menuLayout->addWidget(titleLabel, 0, Qt::AlignTop | Qt::AlignCenter);

    QLabel* subtitleLabel = new QLabel(" We rescue, rehabilitate, and rehome dogs with endless compassion. Because every dog \n deserves a happy ending.\n Choose one of the options below");
    QFont subtitleFont("Delius", 12, QFont::Medium);
    subtitleLabel->setFont(subtitleFont);
    subtitleLabel->setAlignment(Qt::AlignLeft);
    menuLayout->addWidget(subtitleLabel, 0, Qt::AlignLeft);

    menuLayout->addStretch(1);  // Adds flexible space
    QGridLayout* buttonsLayout = new QGridLayout();

    // Menu buttons
    viewDogsButton = new QPushButton("Show dogs");
    viewDogsButton->setFixedSize(200, 70);
    viewFilteredDogsButton = new QPushButton("Filter dogs");
    viewFilteredDogsButton->setFixedSize(200, 70);
    openAdoptionListButton = new QPushButton("Open list in file");
    openAdoptionListButton->setFixedSize(200, 70);
    backButton = new QPushButton("Back to main menu");
    backButton->setFixedSize(200, 70);

    buttonsLayout->addWidget(viewDogsButton, 0, 0);
    buttonsLayout->addWidget(viewFilteredDogsButton, 0, 1);
    buttonsLayout->addWidget(openAdoptionListButton, 1, 1);
    buttonsLayout->addWidget(backButton, 1, 0);

    menuLayout->addLayout(buttonsLayout);
    menuLayout->addStretch(1);

    // ===== DOG VIEW PAGE =====
    dogViewPage = new QWidget();
    QVBoxLayout* dogViewLayout = new QVBoxLayout(dogViewPage);

    QLabel* dogViewTitle = new QLabel("Dog Details");
    dogViewTitle->setFont(titleFont);
    dogViewTitle->setAlignment(Qt::AlignCenter);
    dogViewLayout->addWidget(dogViewTitle);

    // Dog information display
    QGroupBox* dogInfoBox = new QGroupBox("Information");
    QVBoxLayout* dogInfoLayout = new QVBoxLayout(dogInfoBox);

    dogNameLabel = new QLabel("Name: ");
    dogBreedLabel = new QLabel("Breed: ");
    dogAgeLabel = new QLabel("Age: ");
    dogPhotoLabel = new QLabel("Photo URL: ");

    dogInfoLayout->addWidget(dogNameLabel);
    dogInfoLayout->addWidget(dogBreedLabel);
    dogInfoLayout->addWidget(dogAgeLabel);
    dogInfoLayout->addWidget(dogPhotoLabel);

    dogViewLayout->addWidget(dogInfoBox);

    // Dog view buttons
    QHBoxLayout* dogButtonsLayout = new QHBoxLayout();
    nextDogButton = new QPushButton("Next Dog");
    adoptDogButton = new QPushButton("Adopt Dog");
    backToDogMenuButton = new QPushButton("Back to Menu");

    dogButtonsLayout->addWidget(nextDogButton);
    dogButtonsLayout->addWidget(adoptDogButton);
    dogButtonsLayout->addWidget(backToDogMenuButton);

    dogViewLayout->addLayout(dogButtonsLayout);

    // ===== FILTER PAGE =====
    filterPage = new QWidget();
    QVBoxLayout* filterLayout = new QVBoxLayout(filterPage);

    QLabel* filterTitle = new QLabel("Filter Dogs");
    filterTitle->setFont(titleFont);
    filterTitle->setAlignment(Qt::AlignCenter);
    filterLayout->addWidget(filterTitle);

    QGroupBox* filterBox = new QGroupBox("Filter Criteria");
    QFormLayout* filterFormLayout = new QFormLayout(filterBox);

    breedFilterEdit = new QLineEdit();
    ageFilterSpinBox = new QSpinBox();
    ageFilterSpinBox->setRange(0, 20);
    ageFilterSpinBox->setValue(20);

    filterFormLayout->addRow("Breed:", breedFilterEdit);
    filterFormLayout->addRow("Maximum Age:", ageFilterSpinBox);

    filterLayout->addWidget(filterBox);

    // Filter buttons
    QHBoxLayout* filterButtonsLayout = new QHBoxLayout();
    applyFilterButton = new QPushButton("Apply Filter");
    clearFilterButton = new QPushButton("Clear Filter");
    backToFilterMenuButton = new QPushButton("Back to Menu");

    filterButtonsLayout->addWidget(applyFilterButton);
    filterButtonsLayout->addWidget(clearFilterButton);
    filterButtonsLayout->addWidget(backToFilterMenuButton);

    filterLayout->addLayout(filterButtonsLayout);

    // ===== ADOPTION LIST PAGE =====
    adoptionListPage = new QWidget();
    QVBoxLayout* adoptionLayout = new QVBoxLayout(adoptionListPage);

    QLabel* adoptionTitle = new QLabel("My Adoption List");
    adoptionTitle->setFont(titleFont);
    adoptionTitle->setAlignment(Qt::AlignCenter);
    adoptionLayout->addWidget(adoptionTitle);

    adoptionTable = new QTableWidget();
    adoptionTable->setColumnCount(4);
    QStringList headers;
    headers << "Name" << "Breed" << "Age" << "Photograph";
    adoptionTable->setHorizontalHeaderLabels(headers);
    adoptionTable->horizontalHeader()->setSectionResizeMode(QHeaderView::Stretch);

    adoptionLayout->addWidget(adoptionTable);

    backToAdoptionMenuButton = new QPushButton("Back to Menu");
    adoptionLayout->addWidget(backToAdoptionMenuButton);

    // Add all pages to stacked widget
    stackedWidget->addWidget(menuPage);
    stackedWidget->addWidget(dogViewPage);
    stackedWidget->addWidget(filterPage);
    stackedWidget->addWidget(adoptionListPage);

    // Add stacked widget to main layout
    mainLayout->addWidget(stackedWidget);
}

void UserWidget::connectSignalsAndSlots() {
    // Connect menu buttons
    connect(viewDogsButton, &QPushButton::clicked, this, &UserWidget::onViewDogsClicked);
    connect(viewFilteredDogsButton, &QPushButton::clicked, this, &UserWidget::onViewFilteredDogsClicked);
    connect(openAdoptionListButton, &QPushButton::clicked, this, &UserWidget::onOpenAdoptionListClicked);
    connect(backButton, &QPushButton::clicked, this, &UserWidget::onBackClicked);

    // Connect dog view buttons
    connect(nextDogButton, &QPushButton::clicked, this, &UserWidget::onNextDogClicked);
    connect(adoptDogButton, &QPushButton::clicked, this, &UserWidget::onAdoptDogClicked);
    connect(backToDogMenuButton, &QPushButton::clicked, this, &UserWidget::onBackClicked);

    // Connect filter buttons
    connect(applyFilterButton, &QPushButton::clicked, this, &UserWidget::onApplyFilterClicked);
    connect(clearFilterButton, &QPushButton::clicked, this, &UserWidget::onClearFilterClicked);
    connect(backToFilterMenuButton, &QPushButton::clicked, this, &UserWidget::onBackClicked);

}

void UserWidget::showDog(const Dog* dog) {
    if (dog) {
        dogNameLabel->setText("Name: " + QString::fromStdString(dog->getName()));
        dogBreedLabel->setText("Breed: " + QString::fromStdString(dog->getBreed()));
        dogAgeLabel->setText("Age: " + QString::number(dog->getAge()));
        dogPhotoLabel->setText("Photograph: " + QString::fromStdString(dog->getPhotograph()));
        dogPhotoLabel->setOpenExternalLinks(true);
        // Enable adopt button
        adoptDogButton->setEnabled(true);

    }
    else {
        clearDogDisplay();
    }
}

void UserWidget::clearDogDisplay() {
    dogNameLabel->setText("Name: ");
    dogBreedLabel->setText("Breed: ");
    dogAgeLabel->setText("Age: ");
    dogPhotoLabel->setText("Photo URL: ");
    adoptDogButton->setEnabled(false);
}

void UserWidget::updateDogView() {
    if (currentDogIndex >= 0 && currentDogIndex < currentDogs.size()) {
        const Dog& currentDog = currentDogs[currentDogIndex];
        dogNameLabel->setText("Name: " + QString::fromStdString(currentDog.getName()));
        dogBreedLabel->setText("Breed: " + QString::fromStdString(currentDog.getBreed()));
        dogAgeLabel->setText("Age: " + QString::number(currentDog.getAge()));
        dogPhotoLabel->setText("Photograph: " "<a href=\"" + QString::fromStdString(currentDog.getPhotograph()) + "\">Photo URL</a>");
        dogPhotoLabel->setOpenExternalLinks(true);
        // Enable adopt button
        adoptDogButton->setEnabled(true);
    }
    else {
        clearDogDisplay();
    }
}

// Slot implementations
void UserWidget::onViewDogsClicked() {
    try {
        currentDogs = service->getAllDogs();
        currentDogIndex = 0;
        if (!currentDogs.empty()) {
            updateDogView();
        }
        else {
            QMessageBox::information(this, "No Dogs", "There are no dogs available.");
            clearDogDisplay();
        }
        stackedWidget->setCurrentWidget(dogViewPage);
    }
    catch (const std::exception& e) {
        QMessageBox::warning(this, "Error", QString("Failed to load dogs: %1").arg(e.what()));
    }
}

void UserWidget::onViewFilteredDogsClicked() {
    stackedWidget->setCurrentWidget(filterPage);
}


void UserWidget::onSaveAdoptionListClicked() {
    QMessageBox::information(this, "Save Adoption List", "Your adoption list is automatically saved when you adopt a dog.");
}

void UserWidget::onOpenAdoptionListClicked() {
    try {
        adoptionList->displayList();
    }
    catch (const std::exception& e) {
        QMessageBox::warning(this, "Error", QString("Failed to open adoption list: %1").arg(e.what()));
    }
}

void UserWidget::onBackClicked() {
    // When back button is clicked, emit the signal for MainWindow
    if (sender() == backButton) {
        emit backButtonClicked();
    }
    else {
        // For other back buttons, just go back to the menu page
        stackedWidget->setCurrentWidget(menuPage);
    }
}

void UserWidget::onNextDogClicked() {
    if (!currentDogs.empty()) {
        currentDogIndex = (currentDogIndex + 1) % currentDogs.size();
        updateDogView();
    }
}

void UserWidget::onAdoptDogClicked() {
    if (currentDogIndex >= 0 && currentDogIndex < currentDogs.size()) {
        try {
            const Dog& currentDog = currentDogs[currentDogIndex];

            // Save to adoption list
            adoptionList->save(currentDog);
            adoptionRepo->adoptDog(currentDog);

            QMessageBox::information(this, "Adoption Successful",
                QString("You have successfully adopted %1!").arg(QString::fromStdString(currentDog.getName())));

            // Refresh the dog list after adoption
            currentDogs = service->getAllDogs();
            if (currentDogs.empty()) {
                clearDogDisplay();
                QMessageBox::information(this, "No Dogs", "There are no more dogs available.");
            }
            else {
                currentDogIndex = currentDogIndex % currentDogs.size();
                updateDogView();
            }
        }
        catch (const std::exception& e) {
            QMessageBox::warning(this, "Adoption Error", QString("Failed to adopt dog: %1").arg(e.what()));
        }
    }
}

void UserWidget::onApplyFilterClicked() {
    QString breedFilter = breedFilterEdit->text();
    int ageFilter = ageFilterSpinBox->value();

    try {
        // Filter dogs based on criteria
        std::vector<Dog> allDogs = service->getAllDogs();
        currentDogs.clear();

        for (const Dog& dog : allDogs) {
            bool breedMatch = breedFilter.isEmpty() || QString::fromStdString(dog.getBreed()).toLower() == breedFilter.toLower();
            bool ageMatch = dog.getAge() <= ageFilter;

            if (breedMatch && ageMatch) {
                currentDogs.push_back(dog);
            }
        }

        if (currentDogs.empty()) {
            QMessageBox::information(this, "Filter Results", "No dogs match your filter criteria.");
            clearDogDisplay();
        }
        else {
            currentDogIndex = 0;
            updateDogView();
            stackedWidget->setCurrentWidget(dogViewPage);
        }
    }
    catch (const std::exception& e) {
        QMessageBox::warning(this, "Filter Error", QString("Failed to filter dogs: %1").arg(e.what()));
    }
}

void UserWidget::onClearFilterClicked() {
    breedFilterEdit->clear();
    ageFilterSpinBox->setValue(20);
}
