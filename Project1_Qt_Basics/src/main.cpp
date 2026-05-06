#include <QApplication>
#include "MainWindow.h"

int main(int argc, char* argv[]) {
    QApplication app(argc, argv);

    MainWindow window;
    window.setWindowTitle("Qt Basics - ECDIS Starter");
    window.resize(640, 420);
    window.show();

    return app.exec();
}
