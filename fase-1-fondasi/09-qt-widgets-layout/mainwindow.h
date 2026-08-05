#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <QPushButton>
#include <QLabel>
#include <QVBoxLayout>
#include <QLineEdit>

class MainWindow : public QMainWindow {
    Q_OBJECT

public:
    explicit MainWindow(QWidget* parent = nullptr);

private slots:
    void onUpdatePosisi();
    void onResetCount();

private:
    QLabel*      labelPosisi;
    QPushButton* btnUpdate;
    QPushButton* btnReset;
    int          updateCount;
    QLineEdit*   inputNamaKapal;
};

#endif
