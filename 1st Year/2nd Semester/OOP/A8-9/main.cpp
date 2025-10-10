#include "mainWindow.h"
#include "userwidget.h"
#include <QtWidgets/QApplication>
#include "service.h"
#include "repository.h"

int main(int argc, char *argv[])
{   
    Repository rep;
    std::shared_ptr<UserRepository> adoptionRepo;
    DogService service();
    QApplication a(argc, argv);
    MainWindow w;
    w.show();
    return a.exec();
}
