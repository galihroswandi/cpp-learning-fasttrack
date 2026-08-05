#include "mainwindow.h"

#include <QApplication>

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);
    MainWindow w;
    w.setWindowTitle("Thread Basic");
    w.resize(600, 400);
    w.show();
    return QApplication::exec();
}
