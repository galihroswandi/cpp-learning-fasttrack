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










