#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <QPushButton>
#include <QLabel>
#include <QVBoxLayout>

class MainWindow: public QMainWindow
{
    Q_OBJECT;

public:
    explicit MainWindow(QWidget* parent = nullptr);

private slots:
    void onToggleTheme();

private:
    QPushButton* btnPrimary;
    QPushButton* btnDanger;
    QPushButton* btnToggle;
    QPushButton* btnAdd;
    QLabel* labelStatus;
    QLabel* labelDescription;
    bool darkMode;

    void applyTheme();
};

#endif // MAINWINDOW_H
