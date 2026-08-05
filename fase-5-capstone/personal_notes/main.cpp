#include "mainwindow.h"
#include <QApplication>
#include <QSplitter>
#include <QtSql/QSqlDatabase>

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);

    QSqlDatabase db = QSqlDatabase::addDatabase("QSQLITE");
    db.setDatabaseName("personal_note.db");

    if(!db.open())
    {
        qCritical() << "Gagal membuka database " << db.lastError().text();
    }

    QString sql = R"(
        CREATE TABLE IF NOT EXISTS notes (
            id INTEGER PRIMARY KEY AUTOINCREMENT,
            title TEXT NOT NULL DEFAULT '',
            content TEXT NOT NULL DEFAULT '',
            created_at DATETIME NOT NULL DEFAULT CURRENT_TIMESTAMP,
            updated_at DATETIME NOT NULL DEFAULT CURRENT_TIMESTAMP
        )
    )";

    QSqlQuery query;
    if(!query.exec(sql))
    {
        qWarning() << "Gagal create table " << query.lastError().text();
    }


    MainWindow w;
    w.setWindowTitle("Catatan Saya");
    w.show();

    return QApplication::exec();
}
