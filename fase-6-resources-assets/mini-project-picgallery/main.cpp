// TODO MINI-PROJECT FASE 6 — PicGallery i18n
//
// Tugas lo di file ini:
// 1. Load font custom dari QRC (kalau lo include di resources.qrc)
// 2. Load dark theme dari ":/themes/dark.qss" → qApp->setStyleSheet
// 3. Setup QTranslator untuk bisa switch language runtime
// 4. Buat MainWindow + connect signal language switch ke loadLang lambda
// 5. Set qApp->setFont() pakai family yang lo load dari QRC
//
// Pattern referensi:
// - Topik 28 (QFont): QFontDatabase::addApplicationFont + applicationFontFamilies
// - Topik 29 (i18n): QTranslator + installTranslator/removeTranslator
// - Topik 26 (QRC): akses asset via ":/prefix/path"

#include "mainwindow.h"
#include "loadfont.h"

#include <QApplication>
#include <QFile>
#include <QTextStream>
#include <QTranslator>

int main(int argc, char* argv[]) {
    QApplication app(argc, argv);

    // TODO: Load font custom (opsional kalau lo include font di QRC)
    QString family = LoadFont();
    app.setFont(family);


    // TODO: Load dark theme QSS dari QRC
    QString globalStyle;
    QFile themeFile(":/themes/dark.qss");
    if(themeFile.open(QIODevice::ReadOnly | QIODevice::Text))
    {
        QTextStream in(&themeFile);
        globalStyle = in.readAll();
        themeFile.close();
    }

    // TODO: Setup QTranslator + loadLang lambda
    QTranslator translator;
    auto loadLang = [&](const QString code){
        if(code == "en"){
            app.removeTranslator(&translator);
            return;
        }

        QString qmPath = QString(":/i18n/app_%1.qm").arg(code);
        if(translator.load(qmPath)){
            app.installTranslator(&translator);
        }
    };

    app.setStyleSheet(globalStyle);
    MainWindow window;
    QObject::connect(&window, &MainWindow::changeLanguageRequested, &app, loadLang);
    window.show();
    window.resize(768, 600);
    return app.exec();
}
