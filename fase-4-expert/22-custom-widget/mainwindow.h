#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <QSize>
#include <QPaintEvent>
#include <QEnterEvent>
#include <QEvent>
#include <QMouseEvent>
#include <QString>


class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    explicit MainWindow(QWidget *parent = nullptr);
};
#endif // MAINWINDOW_H
