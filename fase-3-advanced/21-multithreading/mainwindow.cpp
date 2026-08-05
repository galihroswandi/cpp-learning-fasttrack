#include "mainwindow.h"

static int tugasBerat()
{
    // Simulasi proses berat - jalan di backgrund thread
    int hasil = 0;
    for(int i = 0; i < 5; i++)
    {
        QThread::sleep(1); // Simulasi kerja 1 detik
        hasil += i * 100;
    }

    return hasil;
}

MainWindow::MainWindow(QWidget *parent) : QMainWindow(parent)
{
    QWidget* central = new QWidget(this);
    setCentralWidget(central);

    btnMulai = new QPushButton("Mulai Proses", this);
    labelStatus = new QLabel("Siap", this);
    progressBar = new QProgressBar(this);
    progressBar->setRange(0, 0);
    progressBar->hide();

    watcher = new QFutureWatcher<int>(this);
    connect(watcher, &QFutureWatcher<int>::finished, this, &MainWindow::onSelesai);

    QVBoxLayout* layout = new QVBoxLayout(central);
    layout->addWidget(btnMulai);
    layout->addWidget(progressBar);
    layout->addWidget(labelStatus);

    connect(btnMulai, &QPushButton::clicked, this, &MainWindow::onMulai);
}

void MainWindow::onMulai()
{
    btnMulai->setEnabled(false);
    labelStatus->setText("Memproses...");
    progressBar->show();

    QFuture<int> future = QtConcurrent::run(tugasBerat);
    watcher->setFuture(future);
}

void MainWindow::onSelesai()
{
    int hasil = watcher->result();

    btnMulai->setEnabled(true);
    progressBar->hide();
    labelStatus->setText("Selesai! Hasil: " + QString::number(hasil));
}