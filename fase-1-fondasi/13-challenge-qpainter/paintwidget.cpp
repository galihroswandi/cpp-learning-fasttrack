#include "paintwidget.h"

PaintWidget::PaintWidget(QWidget* parent): QWidget(parent) {

}

void PaintWidget::paintEvent(QPaintEvent* event)
{
    QPainter painter(this);
    painter.setRenderHint(QPainter::Antialiasing);

    painter.fillRect(rect(), QColor(30,36,50));

    painter.setPen(QPen(QColor(255, 50, 50), 2, Qt::DashLine));
    painter.setBrush(QBrush(QColor(0, 150, 255, 80)));
    painter.drawEllipse(QPoint(width()/2, height()/2), 40, 40);

    painter.drawLine(0, 0, width(), height());

    painter.drawText(QPoint(260, 150), "Qt Painter");
}