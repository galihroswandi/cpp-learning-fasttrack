#include "chartwidget.h"

ChartWidget::ChartWidget(QWidget* parent) : QWidget(parent), shipLat(-6.2088), shipLon(106.8456)
{
    updateCount = 0;
    timer = new QTimer(this);
    connect(timer, &QTimer::timeout, this, &ChartWidget::moveShip);
    timer->start(800);

    setMinimumSize(600, 400);
}

void ChartWidget::paintEvent(QPaintEvent* event)
{
    QPainter painter(this);
    painter.setRenderHint(QPainter::Antialiasing);

    // Background - warna laut
    painter.fillRect(rect(), QColor(20, 60, 120));

    // Grid garis koordinat
    painter.setPen(QPen(QColor(40, 80, 140), 1));
    for(int x = 0; x < width(); x += 50)
        painter.drawLine(x, 0, x, height());
    for(int y = 0; y < height(); y+=50)
        painter.drawLine(0, y, width(), y);

    // Posisi kapal - konversi koordinat ke pixel
    int px = (int)((shipLon - 106.0) * 200 + width() /2);
    int py = (int)((shipLat + 6.5) * (-200) + height() / 2);

    // Gambar kapal sebagai segitiga
    QPolygon ship;
    ship << QPoint(px, py - 12)
         << QPoint(px - 8, py + 8)
         << QPoint(px + 8, py + 8);
    painter.setBrush(QColor(255, 200, 0));
    painter.setPen(Qt::NoPen);
    painter.drawPolygon(ship);

    // Label koordinat
    painter.setPen(Qt::white);
    painter.drawText(px + 12, py, QString("Lat: %1 Lon: %2").arg(shipLat).arg(shipLon));

    // Danger Zone
    painter.setPen(QPen(QColor(255, 50, 50), 2, Qt::DashLine));
    painter.setBrush(Qt::NoBrush);
    painter.drawEllipse(QPoint(px, py), 40, 40);

    // Counter dipojok kiri atas
    painter.setPen(Qt::white);
    painter.drawText(10, 20, QString("Update : %1").arg(updateCount));
}

void ChartWidget::moveShip()
{
    shipLon += 0.05;
    updateCount++;
    update();
}

void ChartWidget::toggleTimer()
{
    if(timer->isActive())
        timer->stop();
    else
        timer->start(800);

}