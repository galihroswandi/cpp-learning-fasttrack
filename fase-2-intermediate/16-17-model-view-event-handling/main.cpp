#include "mainwindow.h"

#include <QApplication>

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);
    MainWindow w;
    w.setWindowTitle("Model/View");
    w.resize(400, 300);
    w.show();
    return QApplication::exec();
}
