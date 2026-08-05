#include <QApplication>
#include <QTranslator>
#include <QDebug>
#include "mainwindow.h"

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);

    QTranslator translator;
    auto loadLang = [&](const QString& code) {
        if (code == "en") {
            qApp->removeTranslator(&translator);
            qDebug() << "Switched to english (default)";
            return;
        }

        QString qmPath = QString(":/i18n/app_%1.qm").arg(code);
        if (translator.load(qmPath)) {
            qApp->installTranslator(&translator);
            qDebug() << "Loaded translation:" << qmPath;
        } else {
            qDebug() << "Failed to load path:" << qmPath;
        }
    };

    MainWindow window;
    QObject::connect(&window, &MainWindow::changeLanguageRequested, &a, loadLang);
    window.resize(400, 200);
    window.show();

    return QApplication::exec();
}
