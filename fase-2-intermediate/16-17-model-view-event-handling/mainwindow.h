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
#include <QKeyEvent>
#include <QMouseEvent>
#include <QCloseEvent>
#include <QMessageBox>
#include <QStatusBar>

class MainWindow: public QMainWindow
{
    Q_OBJECT;

public:
    explicit MainWindow(QWidget* parent = nullptr);

protected:
    void keyPressEvent(QKeyEvent* event) override;
    void mouseMoveEvent(QMouseEvent* event) override;
    void closeEvent(QCloseEvent* event) override;

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
