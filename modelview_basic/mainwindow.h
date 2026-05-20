#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <QStringListModel>
#include <QListView>
#include <QLineEdit>
#include <QPushButton>
#include <QVBoxLayout>
#include <QHBoxLayout>
#include <QComboBox>

class MainWindow: public QMainWindow
{
    Q_OBJECT;

public:
    explicit MainWindow(QWidget* parent = nullptr);

private slots:
    void onTambah();
    void onHapus();

private:
    QStringListModel* model;
    QComboBox* comboBox;
    QListView* listView2;
    QLineEdit* input;
    QPushButton* btnTambah;
    QPushButton* btnHapus;
};

#endif // MAINWINDOW_H
