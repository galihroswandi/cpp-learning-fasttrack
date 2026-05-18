#include "mainwindow.h"

MainWindow::MainWindow(QWidget *parent) : QMainWindow(parent), updateCount(0)
{
    setWindowTitle("ECDIS Monitor");
    setMinimumSize(400, 200);

    QWidget *central = new QWidget(this);
    setCentralWidget(central);

    QVBoxLayout* layout = new QVBoxLayout(central);
    labelPosisi = new QLabel("Posisi: Menunggu update...", this);
    btnUpdate = new QPushButton("Update Posisi GPS", this);
    btnReset = new QPushButton("Reset Count", this);
    inputNamaKapal = new QLineEdit();

    layout->addWidget(labelPosisi);
    layout->addWidget(btnUpdate);
    layout->addWidget(btnReset);
    layout->addWidget(inputNamaKapal);

    connect(btnUpdate, &QPushButton::clicked, this, &MainWindow::onUpdatePosisi);
    connect(btnReset, &QPushButton::clicked, this, &MainWindow::onResetCount);
}

void MainWindow::onUpdatePosisi()
{
    updateCount++;
    QString posisi = QString("Posisi #%1: Lat %2, Lon %3")
                         .arg(updateCount)
                         .arg(-6.2088 + updateCount * 0.01)
                         .arg(106.8456+updateCount*0.01);
    labelPosisi->setText(posisi);
}

void MainWindow::onResetCount()
{
    updateCount = 0;
    QString posisi = QString("Posisi #%1: Lat %2, Lon %3")
                         .arg(updateCount)
                         .arg(-6.2088)
                         .arg(106.8456);
    labelPosisi->setText(posisi);
}