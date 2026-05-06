#include <QApplication>
#include <QString>
#include "MainWindow.h"

int main(int argc, char* argv[]) {
    QApplication app(argc, argv);

    QString defaultFile;
    if (argc > 1) {
        defaultFile = QString::fromLocal8Bit(argv[1]);
    } else {
        defaultFile = QStringLiteral("../data/sample_chart.s57");
    }

    MainWindow window(defaultFile);
    window.setWindowTitle("ECDIS Integration - Chart Viewer");
    window.resize(1000, 760);
    window.show();

    return app.exec();
}
