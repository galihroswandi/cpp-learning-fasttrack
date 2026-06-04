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

#include <QApplication>
#include <QTranslator>
#include <QFile>
#include <QDebug>
#include "mainwindow.h"

int main(int argc, char* argv[]) {
    QApplication app(argc, argv);

    // TODO: Load font custom (opsional kalau lo include font di QRC)

    // TODO: Load dark theme QSS dari QRC

    // TODO: Setup QTranslator + loadLang lambda

    MainWindow window;
    window.show();
    return app.exec();
}
