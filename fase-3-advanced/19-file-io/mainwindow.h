#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <QTextEdit>
#include <QLabel>
#include <QPushButton>
#include <QString>
#include <QWidget>
#include <QHBoxLayout>
#include <QFileDialog>
#include <QFile>
#include <QTextStream>
#include <QCloseEvent>
#include <QMessageBox>

class MainWindow: public QMainWindow
{
    Q_OBJECT;

public:
    explicit MainWindow(QWidget* parent = nullptr);

protected:
    void closeEvent(QCloseEvent* event) override;

private slots:
    void onBuka();
    void onSimpan();

private:
    QTextEdit* editor;
    QLabel* labelFile;
    QPushButton* btnBuka;
    QPushButton* btnSimpan;
    QString filePath;
};

#endif // MAINWINDOW_H
