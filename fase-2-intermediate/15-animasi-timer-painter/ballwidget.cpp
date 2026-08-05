#include "ballwidget.h"
#include <QPainter>

BallWidget::BallWidget(QWidget* parent): QWidget(parent), ballX(100), ballY(200), radius(30), dx(3), dy(2)
{
    setMinimumSize(600, 400);

    timer = new QTimer(this);
    connect(timer, &QTimer::timeout, this, &BallWidget::moveBall);
    timer->start(16);
}

void BallWidget::moveBall()
{

    ballX += dx;
    ballY += dy;

    if(ballX - radius < 0 || ballX + radius > width()) dx = -dx;
    if(ballY - radius < 0 || ballY + radius > height()) dy = -dy;

    update();
}

void BallWidget::paintEvent(QPaintEvent* event)
{
    QPainter painter(this);
    painter.setRenderHint(QPainter::Antialiasing);

    painter.fillRect(rect(), QColor(20, 20, 40));

    painter.setBrush(QColor(50, 180, 255));
    painter.setPen(Qt::NoPen);
    painter.drawEllipse(QPoint(ballX, ballY), radius, radius);
}