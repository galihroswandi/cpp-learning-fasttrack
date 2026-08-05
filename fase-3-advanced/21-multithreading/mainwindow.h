#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <QPushButton>
#include <QLabel>
#include <QProgressBar>
#include <QFutureWatcher>
#include <QWidget>
#include <QThread>
#include <QVBoxLayout>
#include <QtConcurrent/QtConcurrent>
#include <QString>

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    explicit MainWindow(QWidget *parent = nullptr);

private slots:
    void onMulai();
    void onSelesai();

private:
    QPushButton* btnMulai;
    QLabel* labelStatus;
    QProgressBar* progressBar;
    QFutureWatcher<int>* watcher;
};
#endif // MAINWINDOW_H
