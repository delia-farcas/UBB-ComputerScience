#include "mainWindow.h"

MainWindow::MainWindow(QWidget* parent)
    : repo("dogs.txt"), service(repo), user_srv(user_srv), userRepo(std::make_shared<UserRepository>()), FileType("csv"), FilePath("dogs.csv") {
    setWindowTitle("Dog shelter application");
    setFixedSize(700, 450);

    stackedWidget = new QStackedWidget(this);
    setCentralWidget(stackedWidget);
    if (repo.getSize() == 0)
        try {
            service.generateSampleDogs();
        }
        catch (const std::exception& e) {
            QMessageBox::warning(this, "Warning", QString("Error generating sample dogs: %1").arg(e.what()));
        }
        this->setupMainWindow();
}

MainWindow::~MainWindow() {}

void MainWindow::setupMainWindow() {
    MainMenuWidget = new QWidget();
    QVBoxLayout* mainLayout = new QVBoxLayout(MainMenuWidget);
    mainLayout->setSpacing(10);
    mainLayout->setContentsMargins(30, 25, 25, 25);

    QLabel* titleLabel = new QLabel{ "THE ORIGINAL DOG SHELTER APP" };
    QFont titleFont("Orbitron", 22, QFont::Medium);
    titleLabel->setFont(titleFont);
    titleLabel->setAlignment(Qt::AlignCenter);
    mainLayout->addWidget(titleLabel, 0, Qt::AlignTop | Qt::AlignHCenter);


    // Subtitle label
    QFont subtitleFont("Red Hat Display", 12, QFont::Normal);
    QLabel* subtitleLabel = new QLabel{ "From shelter to family, from stray to adored\n love is the magic no store can afford" };
    subtitleLabel->setFont(subtitleFont);
    subtitleLabel->setAlignment(Qt::AlignCenter);
    mainLayout->addWidget(subtitleLabel, 0, Qt::AlignHCenter);  // Centers horizontally

    // Spacer to push buttons up (adjust stretch factor as needed)
    mainLayout->addStretch(1);  // Adds flexible space

    // Buttons (centered horizontally)
    QGridLayout* buttonLayout = new QGridLayout;
    buttonLayout->setSpacing(30);

    QPushButton* adminButton = new QPushButton("Admin mode");
    QPushButton* userButton = new QPushButton("User mode");
    QPushButton* adoptionButton = new QPushButton("View adoption list");
    QFont buttonFont("Red Hat Display", 11, QFont::Medium);
    adminButton->setFont(buttonFont);
    userButton->setFont(buttonFont);
    adoptionButton->setFont(buttonFont);
    adminButton->setFixedSize(150, 45);
    userButton->setFixedSize(150, 45);
    adoptionButton->setFixedSize(150, 45);

    buttonLayout->addWidget(userButton, 0, 0);
    buttonLayout->addWidget(adminButton, 0, 2);
    buttonLayout->addWidget(adoptionButton, 1, 1);
    mainLayout->addLayout(buttonLayout);

    // File type combo (raised by reducing spacer stretch)
    mainLayout->addStretch(1);  // Less space than before buttons
    QHBoxLayout* fileTypeLayout = new QHBoxLayout();
    fileTypeLayout->addStretch();  // Centers the combo box
    fileTypeLayout->addWidget(new QLabel("Select file type for adoption list:"));
    fileTypeComboBox = new QComboBox();
    fileTypeComboBox->addItem("CSV");
    fileTypeComboBox->addItem("HTML");
    fileTypeLayout->addWidget(fileTypeComboBox);
    fileTypeLayout->addStretch();  // Balances the centering
    mainLayout->addLayout(fileTypeLayout);

    // Connect the file type combo box to update the file type
    connect(fileTypeComboBox, &QComboBox::currentTextChanged, this, [this](const QString& text) {
        FileType = text.toLower();
        if (FileType == "csv") {
            FilePath = "dogs.csv";
        }
        else if (FileType == "html") {
            FilePath = "dogs.html";
        }
        });

    connect(adminButton, &QPushButton::clicked, this, &MainWindow::clicked_adminButton);
    connect(userButton, &QPushButton::clicked, this, &MainWindow::clicked_userButton);
    connect(adoptionButton, &QPushButton::clicked, this, &MainWindow::clicked_adoptionButton);

    stackedWidget->addWidget(MainMenuWidget);
    stackedWidget->setCurrentWidget(MainMenuWidget);
}


void MainWindow::clicked_backToMain() {
    stackedWidget->setCurrentWidget(MainMenuWidget);
}

void MainWindow::clicked_adminButton() {
    if (!adminWidget) {
        adminWidget = new AdminWidget(&service);
        connect(adminWidget, &AdminWidget::backButtonClicked, this, &MainWindow::clicked_backToMain);
        stackedWidget->addWidget(adminWidget);
    }
    stackedWidget->setCurrentWidget(adminWidget);
}

void MainWindow::clicked_userButton() {
    if (userWidget) {
        // Remove old widget if it exists
        stackedWidget->removeWidget(userWidget);
        delete userWidget;
        userWidget = nullptr;
    }

    // Create a new UserWidget with current file type settings
    userWidget = new UserWidget(&service, userRepo, FileType, FilePath);
    connect(userWidget, &UserWidget::backButtonClicked, this, &MainWindow::clicked_backToMain);
    stackedWidget->addWidget(userWidget);
    stackedWidget->setCurrentWidget(userWidget);
}

void MainWindow::clicked_adoptionButton() {
    if (!adoptWidget) {
        adoptWidget = new QtWidgetsClass(userRepo);
        stackedWidget->addWidget(adoptWidget);
    }
    connect(adoptWidget, &QtWidgetsClass::backButtonClicked, this, &MainWindow::clicked_backToMain);
    
    stackedWidget->setCurrentWidget(adoptWidget);
}
