#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <QtSql/QSqlDatabase>
#include <QtSql/QSqlTableModel>
#include <QListView>
#include <QPushButton>
#include <QLabel>
#include <QLineEdit>
#include <QHBoxLayout>
#include <QVBoxLayout>
#include <QMessageBox>
#include <QtSql/QSqlQuery>

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    explicit MainWindow(QWidget *parent = nullptr);
    ~MainWindow();

private slots:
    void onTambah();
    void onHapus();

private:
    void setupDatabase();
    void refreshData();

    QSqlDatabase db;
    QSqlTableModel* model;
    QListView* listView;
    QLineEdit* input;
    QPushButton* btnTambah;
    QPushButton* btnHapus;
    QLabel* labelInfo;
};
#endif // MAINWINDOW_H
