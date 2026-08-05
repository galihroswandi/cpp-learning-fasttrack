#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <QLabel>
#include <QLineEdit>
#include <QPushButton>
#include <QVBoxLayout>
#include <QHBoxLayout>

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    explicit MainWindow(QWidget *parent = nullptr);

public slots:
    void onSimulasiUpdate();
    void onReset();
    void uiUpdate();

private:
    QLabel* labelNamaKapal;
    QLabel* labelPosisi;
    QLabel* labelKecepatan;
    QLabel* statusLabel;
    QLabel* formLabel;
    QLineEdit* inputNamaKapal;
    QPushButton* simulasiUpdate;
    QPushButton* reset;

    QString namaKapal;
    double lat;
    double lon;
    double kecepatan;
    bool status;
};
#endif
