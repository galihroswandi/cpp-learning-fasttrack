#include <QApplication>
#include "MainWindow.h"

int main(int argc, char* argv[]) {
    QApplication app(argc, argv);

    MainWindow window;
    window.setWindowTitle("Qt Graphics - ECDIS Chart View");
    window.resize(900, 700);
    window.show();

    return app.exec();
}
