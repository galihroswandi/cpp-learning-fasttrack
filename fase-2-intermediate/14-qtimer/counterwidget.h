#ifndef COUNTERWIDGET_H
#define COUNTERWIDGET_H

#include <QWidget>
#include <QTimer>
#include <QLabel>
#include <QVBoxLayout>
#include <QPushButton>

class CounterWidget : public QWidget {
    Q_OBJECT
public:
    explicit CounterWidget(QWidget* parent = nullptr);

private slots:
    void onTick();
    void onToggle();
    void onReset();

private:
    QTimer* timer;
    QLabel* label;
    QPushButton* toggleButton;
    QPushButton* resetButton;
    int count;
};

#endif
