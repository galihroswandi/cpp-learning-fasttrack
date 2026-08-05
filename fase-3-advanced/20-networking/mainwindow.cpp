#include "mainwindow.h"

MainWindow::MainWindow(QWidget *parent) : QMainWindow(parent)
{
    QWidget* central = new QWidget(this);
    setCentralWidget(central);

    manager = new QNetworkAccessManager(this);
    output = new QTextEdit(this);
    btnFetch = new QPushButton("Fetch Data", this);
    labelStatus = new QLabel("Siap", this);

    output->setReadOnly(true);

    QVBoxLayout* layout = new QVBoxLayout(central);
    layout->addWidget(btnFetch);
    layout->addWidget(labelStatus);
    layout->addWidget(output);

    connect(btnFetch, &QPushButton::clicked, this, &MainWindow::onFetch);
    connect(manager, &QNetworkAccessManager::finished, this, &MainWindow::onReplyFinished);
}

void MainWindow::onFetch()
{
    labelStatus->setText("Fetching...");
    btnFetch->setEnabled(false);

    QNetworkRequest request;
    request.setUrl(QUrl("https://httpbin.org/get"));
    manager->get(request);
}

void MainWindow::onReplyFinished(QNetworkReply* reply)
{
    btnFetch->setEnabled(true);

    if(reply->error() != QNetworkReply::NoError)
    {
        labelStatus->setText("Error: " + reply->errorString());
        reply->deleteLater();
        return;
    }

    QString data = QString::fromUtf8(reply->readAll());
    output->setPlainText(data);
    labelStatus->setText("Selesai -- " + QString::number(data.size()) + " karakter");
    reply->deleteLater();
}