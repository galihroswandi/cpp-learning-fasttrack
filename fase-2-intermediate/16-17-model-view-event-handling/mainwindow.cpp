#include "mainwindow.h"

MainWindow::MainWindow(QWidget* parent): QMainWindow(parent)
{
    QWidget* central = new QWidget(this);
    setCentralWidget(central);
    QVBoxLayout* layout = new QVBoxLayout(central);

    model = new QStringListModel(this);
    model->setStringList({"Jakarta", "Surabaya", "Medan"});

    comboBox = new QComboBox(this);
    listView2 = new QListView(this);
    comboBox->setModel(model);
    listView2->setModel(model);

    input = new QLineEdit(this);
    input->setPlaceholderText("Nama Kota...");
    btnTambah= new QPushButton("Tambah", this);
    btnHapus = new QPushButton("Hapus", this);

    QHBoxLayout* hbox = new QHBoxLayout();
    hbox->addWidget(input);
    hbox->addWidget(btnTambah);
    hbox->addWidget(btnHapus);

    layout->addWidget(comboBox);
    layout->addWidget(listView2);
    layout->addLayout(hbox);

    connect(btnTambah, &QPushButton::clicked, this, &MainWindow::onTambah);
    connect(btnHapus, &QPushButton::clicked, this, &MainWindow::onHapus);

    central->setMouseTracking(true);
}

void MainWindow::onTambah()
{
    QString teks = input->text().trimmed();
    if(teks.isEmpty()) return;

    int row = model->rowCount();
    model->insertRow(row);
    model->setData(model->index(row), teks);
    input->clear();
}

void MainWindow::onHapus()
{
    int idx = comboBox->currentIndex();
    if(idx < 0) return;
    model->removeRow(idx);
}

void MainWindow::keyPressEvent(QKeyEvent* event)
{
    if(event->key() == Qt::Key_Return || event->key() == Qt::Key_Enter)
    {
        onTambah();
    }else if(event->key() == Qt::Key_Delete)
    {
        onHapus();
    }else {
        QMainWindow::keyPressEvent(event);
    }
}

void MainWindow::mouseMoveEvent(QMouseEvent* event)
{
    statusBar()->showMessage(QString("x: %1, y: %2").arg(event->pos().x()).arg(event->pos().y()));
    QMainWindow::mouseMoveEvent(event);
}

void MainWindow::closeEvent(QCloseEvent* event)
{
    QMessageBox::StandardButton jawab = QMessageBox::question(this, "Konfirmasi", "Yakin Mau Keluar?", QMessageBox::Yes | QMessageBox::No);
    if(jawab == QMessageBox::Yes)
    {
        event->accept();
    }else {
        event->ignore();
    }
}








