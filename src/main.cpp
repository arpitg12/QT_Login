#include "mainwindow.h"
#include <QApplication>
#include <QDir>

int main(int argc, char *argv[])
{
    // Set plugin path explicitly if needed
    QCoreApplication::addLibraryPath("./plugins");
    
    QApplication app(argc, argv);
    
    MainWindow w;
    w.show();
    
    return app.exec();
}