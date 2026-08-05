#ifndef BALLWIDGET_H
#define BALLWIDGET_H

#include <QWidget>
#include <QTimer>
#include <QString>

class BallWidget: public QWidget
{
    Q_OBJECT;

public:
    BallWidget(QWidget* parent = nullptr);

protected:
    void paintEvent(QPaintEvent* event) override;

private slots:
    void moveBall();

private:
    QTimer* timer;
    int ballX;
    int ballY;
    int radius;
    int dx; // kecepatan horizonal: + = kanan, - = kiri
    int dy; // kecepatan vertical: + = bawah, - = atas
};

#endif // BALLWIDGET_H
