#ifndef LOADFONT_H
#define LOADFONT_H

#include <QFontDatabase>
#include <QStringList>
#include <QDebug>

QString LoadFont()
{
    QStringList fonts = {
        ":/fonts/light.ttf",
        ":/fonts/regular.ttf",
        ":/fonts/semibold.ttf",
        ":/fonts/bold.ttf"};

    QString family;

    for (const QString &fontPath : fonts)
    {
        int fontId = QFontDatabase::addApplicationFont(fontPath);
        if (fontId == -1)
        {
            qDebug() << "Failed load: " << fontPath;
            continue;
        }

        family = QFontDatabase::applicationFontFamilies(fontId).at(0);
        qDebug() << "Loaded: " << fontPath;
    }

    return family;
};

#endif // LOADFONT_H
