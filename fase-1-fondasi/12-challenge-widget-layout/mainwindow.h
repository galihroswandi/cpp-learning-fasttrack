#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <QVBoxLayout>
#include <QLineEdit>
#include <QLabel>
#include <QPushButton>
#include <QDoubleValidator>

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    explicit MainWindow(QWidget *parent = nullptr);

public slots:
    void onKonversi();

private:
    QLabel* inputSuhuLabel;
    QLineEdit* inputSuhu;
    QPushButton* submitButton;
    QLabel* hasilKonversiText;
};
#endif // MAINWINDOW_H
