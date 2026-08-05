#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <QtNetwork/QNetworkReply>
#include <QtNetwork/QNetworkAccessManager>
#include <QtNetwork/QNetworkRequest>
#include <QUrl>
#include <QTextEdit>
#include <QPushButton>
#include <QLabel>
#include <QWidget>
#include <QVBoxLayout>
#include <QString>

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    explicit MainWindow(QWidget *parent = nullptr);

private slots:
    void onFetch();
    void onReplyFinished(QNetworkReply* reply);

private:
    QNetworkAccessManager* manager;
    QTextEdit* output;
    QPushButton* btnFetch;
    QLabel* labelStatus;
};
#endif // MAINWINDOW_H
