#include "mainwindow.h"
MainWindow::MainWindow(QWidget *parent) : QMainWindow(parent)
{
    QWidget* central = new QWidget(this);
    setCentralWidget(central);

    input = new QLineEdit(this);
    btnTambah = new QPushButton("Tambah", this);
    btnHapus = new QPushButton("Hapus", this);
    labelInfo = new QLabel("", this);
    listView = new QListView(this);

    input->setPlaceholderText("Nama kapal...");

    QHBoxLayout* hbox = new QHBoxLayout();
    hbox->addWidget(input);
    hbox->addWidget(btnTambah);
    hbox->addWidget(btnHapus);

    QVBoxLayout* layout = new QVBoxLayout(central);
    layout->addLayout(hbox);
    layout->addWidget(listView);
    layout->addWidget(labelInfo);

    connect(btnTambah, &QPushButton::clicked, this, &MainWindow::onTambah);
    connect(btnHapus, &QPushButton::clicked, this, &MainWindow::onHapus);

    setupDatabase();
}

MainWindow::~MainWindow()
{
    db.close();
}

void MainWindow::setupDatabase()
{
    db = QSqlDatabase::addDatabase("QSQLITE");
    db.setDatabaseName("kapal.db");

    if(!db.open())
    {
        QMessageBox::critical(this, "Error", "Gagal buka database!");
        return;
    }

    QSqlQuery query;
    query.exec("CREATE TABLE IF NOT EXISTS kapal ("
               "id INTEGER PRIMARY KEY AUTOINCREMENT,"
               "nama TEXT NOT NULL)");

    model = new QSqlTableModel(this, db);
    model->setTable("kapal");
    model->setEditStrategy(QSqlTableModel::OnManualSubmit);
    model->select();

    listView->setModel(model);
    listView->setModelColumn(1); // Tampilkan kolom 'nama' bukan 'id'

    labelInfo->setText(QString("Database: kapal.db | %1 kapal").arg(model->rowCount()));
}

void MainWindow::onTambah()
{
    QString nama = input->text().trimmed();
    if(nama.isEmpty()) return;

    QSqlQuery query;
    query.prepare("INSERT INTO kapal (nama) VALUES (:nama)");
    query.bindValue(":nama", nama);

    if(query.exec())
    {
        model->select();
        input->clear();
        labelInfo->setText(QString("Database: kapal.db | %1 kapal").arg(model->rowCount()));
    }
}


void MainWindow::onHapus()
{
    QModelIndex idx = listView->currentIndex();
    if(!idx.isValid()) return;

    model->removeRow(idx.row());
    model->submitAll();
    model->select();

    labelInfo->setText(QString("Database: kapal.db | %1 kapal").arg(model->rowCount()));
}