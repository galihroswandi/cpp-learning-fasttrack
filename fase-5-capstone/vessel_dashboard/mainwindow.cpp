#include "mainwindow.h"

MainWindow::MainWindow(QWidget *parent) : QMainWindow(parent), lat(0), lon(0), kecepatan(0), namaKapal("--"), status(false)
{
    setWindowTitle("Vessel Dashboard");
    setMinimumSize(400, 200);

    QWidget* central = new QWidget(this);
    setCentralWidget(central);

    QVBoxLayout* layout = new QVBoxLayout(central);
    labelNamaKapal = new QLabel();
    labelPosisi = new QLabel();
    labelKecepatan = new QLabel();
    statusLabel = new QLabel();

    layout->addWidget(labelNamaKapal);
    layout->addWidget(labelPosisi);
    layout->addWidget(labelKecepatan);
    layout->addWidget(statusLabel);

    QHBoxLayout* hlayout = new QHBoxLayout();
    inputNamaKapal = new QLineEdit();
    simulasiUpdate = new QPushButton("Simulasi Update", this);
    reset = new QPushButton("Reset", this);

    QHBoxLayout* formLayout = new QHBoxLayout();

    layout->addLayout(hlayout);
    hlayout->addLayout(formLayout);

    formLabel = new QLabel();
    formLayout->addWidget(formLabel);
    formLayout->addWidget(inputNamaKapal);

    hlayout->addWidget(simulasiUpdate);
    hlayout->addWidget(reset);

    MainWindow::uiUpdate();

    connect(simulasiUpdate, &QPushButton::clicked, this, &MainWindow::onSimulasiUpdate);
    connect(reset, &QPushButton::clicked, this, &MainWindow::onReset);
}

void MainWindow::onSimulasiUpdate()
{
    if(lat == 0 || lon == 0)
    {
        lat = -6.2088;
        lon = 106.8456;
    }

    namaKapal = inputNamaKapal->text();
    kecepatan += 10;
    lat *= 0.5;
    lon *= 0.8;
    status = true;

    MainWindow::uiUpdate();
}

void MainWindow::onReset()
{
    kecepatan = 0;
    lat = -6.2088;
    lon = 106.8456;
    status = false;
    MainWindow::uiUpdate();
}

void MainWindow::uiUpdate()
{
    QString kapalText = QString("Kapal    :  %1")
    .arg(namaKapal);
    labelNamaKapal->setText(kapalText);
    QString posisiText = QString("Posisi    :  Lat %1, Lon %2")
                             .arg(lat)
                             .arg(lon);
    labelPosisi->setText(posisiText);
    QString speedText = QString("Speed   :  %1 knot")
                            .arg(kecepatan);
    labelKecepatan->setText(speedText);
    QString statusBerlayar = QString("Status   : %1")
                                 .arg(status ? "Berlayar" : "Sandar");
    statusLabel->setText(statusBerlayar);

    QString labelText = QString("Nama Kapal");
    formLabel->setText(labelText);
}