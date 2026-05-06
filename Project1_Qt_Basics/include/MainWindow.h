#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>

class QPushButton;
class QLineEdit;
class QLabel;
class QListWidget;
class QSlider;
class QStatusBar;

class MainWindow : public QMainWindow {
    Q_OBJECT

public:
    explicit MainWindow(QWidget* parent = nullptr);
    ~MainWindow() override;

private slots:
    void onLoadChartClicked();
    void onChartNameChanged(const QString& text);
    void onZoomChanged(int value);

private:
    void setupUi();
    void writeLog(const QString& message);

    QWidget* centralWidget;
    QLabel* titleLabel;
    QLineEdit* chartNameInput;
    QPushButton* loadButton;
    QPushButton* clearButton;
    QListWidget* logList;
    QSlider* zoomSlider;
    QLabel* zoomLabel;
    QStatusBar* statusBar;
};

#endif // MAINWINDOW_H
