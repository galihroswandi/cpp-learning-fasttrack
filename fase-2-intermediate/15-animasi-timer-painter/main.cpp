#include "ballwidget.h"

#include <QApplication>

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);
    BallWidget w;
    w.setWindowTitle("Animasi Bola");
    w.show();
    return QApplication::exec();
}
