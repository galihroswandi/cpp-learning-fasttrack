#include "mainwindow.h"

MainWindow::MainWindow(QWidget *parent) : QMainWindow(parent)
{
    QWidget* central = new QWidget(this);
    setCentralWidget(central);

    editor = new QTextEdit(this);
    labelFile = new QLabel("Belum ada file", this);
    btnBuka = new QPushButton("Buka", this);
    btnSimpan = new QPushButton("Simpan", this);

    QHBoxLayout* hbox = new QHBoxLayout();
    hbox->addWidget(btnBuka);
    hbox->addWidget(btnSimpan);
    hbox->addWidget(labelFile);
    hbox->addStretch();

    QVBoxLayout* layout = new QVBoxLayout(central);
    layout->addLayout(hbox);
    layout->addWidget(editor);

    connect(btnBuka, &QPushButton::clicked, this, &MainWindow::onBuka);
    connect(btnSimpan, &QPushButton::clicked, this, &MainWindow::onSimpan);
}

void MainWindow::onBuka()
{
    QString path = QFileDialog::getOpenFileName(this, "Buka File", "", "Text Files (*.txt);;All Files (*)");
    if(path.isEmpty())return;

    QFile file(path);
    if(!file.open(QFile::ReadOnly | QFile::Text))
    {
        labelFile->setText("Gagal Membuka File");
        return;
    }

    QTextStream in(&file);
    editor->setPlainText(in.readAll());
    file.close();

    filePath = path;
    labelFile->setText(QFileInfo(path).fileName());
}

void MainWindow::onSimpan()
{
    if(filePath.isEmpty())
    {
        filePath = QFileDialog::getSaveFileName(this, "Simpan File", "", "Text Files (*.txt)");
        if(filePath.isEmpty()) return;
    }

    QFile file(filePath);
    if(!file.open(QFile::WriteOnly | QFile::Text))
    {
        labelFile->setText("Gagal Menyimpan");
        return;
    }

    QTextStream out(&file);
    out<<editor->toPlainText();
    file.close();
    editor->document()->setModified(false);


    labelFile->setText("Tersimpan: "+QFileInfo(filePath).fileName());
}

void MainWindow::closeEvent(QCloseEvent* event)
{
    if(editor->document()->isModified())
    {
        QMessageBox::StandardButton jawab = QMessageBox::question(
            this,
            "Konfirmasi",
            "Ada perubahan yang belum disimpan. Keluar?",
            QMessageBox::Yes | QMessageBox::No
        );

            if(jawab == QMessageBox::Yes)
            {
                onSimpan();
                event->accept();
            }else
            {
                event->ignore();
            }
    }else {
        event->accept();
    }
}

