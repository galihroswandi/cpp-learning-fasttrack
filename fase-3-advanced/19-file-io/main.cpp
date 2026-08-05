#include "mainwindow.h"

#include <QApplication>

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);
    MainWindow w;
    w.setWindowTitle("Text Editor");
    w.resize(600, 400);
    w.show();
    return QApplication::exec();
}
