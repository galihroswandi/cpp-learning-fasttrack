#ifndef CHARTWIDGET_H
#define CHARTWIDGET_H

#include <QWidget>
#include <QPainter>
#include <QTimer>

class ChartWidget : public QWidget
{
    Q_OBJECT
public:
    explicit ChartWidget(QWidget* parent = nullptr);

protected:
    void paintEvent(QPaintEvent* event) override;

private:
    double shipLat;
    double shipLon;
    QTimer *timer;
    int updateCount;

public slots:
    void moveShip();
    void toggleTimer();
};

#endif // CHARTWIDGET_H
