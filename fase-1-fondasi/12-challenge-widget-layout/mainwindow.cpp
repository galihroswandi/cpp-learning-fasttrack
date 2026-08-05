#include "mainwindow.h"

MainWindow::MainWindow(QWidget *parent): QMainWindow(parent)
{
    setWindowTitle("Konversi Suhu");
    // set minimal size
    setMinimumSize(400, 100);

    // definisi central of UI
    QWidget* central = new QWidget(this);
    QDoubleValidator* validator = new QDoubleValidator(this);
    validator->setNotation(QDoubleValidator::StandardNotation);
    setCentralWidget(central);

    // Definisi Komponent dan conect
    QVBoxLayout* layout = new QVBoxLayout(central);
    QHBoxLayout* hlayout = new QHBoxLayout();

    inputSuhuLabel = new QLabel("Masukan Suhu: ", this);
    hasilKonversiText = new QLabel("Hasil: ", this);
    inputSuhu = new QLineEdit(this);
    inputSuhu->setValidator(validator);
    submitButton = new QPushButton("Konversi", this);

    layout->addLayout(hlayout);
    hlayout->addWidget(inputSuhuLabel);
    hlayout->addWidget(inputSuhu);
    layout->addWidget(hasilKonversiText);
    layout->addWidget(submitButton);

    connect(submitButton, &QPushButton::clicked, this, &MainWindow::onKonversi);
}

void MainWindow::onKonversi()
{
    QString inputUser = inputSuhu->text();
    double inputUserDouble = inputUser.toDouble();

    double hasilKonversi = (inputUserDouble * 9/5) + 32;
    QString hasil = QString("Hasil: %1 °F")
                        .arg(QString::number(hasilKonversi, 'f', 2));
    hasilKonversiText->setText(hasil);
}