#include "mainwindow.h"

#include <QApplication>

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);
    MainWindow w;
    w.setWindowTitle("Database Kapal");
    w.resize(400, 350);
    w.show();
    return QApplication::exec();
}
