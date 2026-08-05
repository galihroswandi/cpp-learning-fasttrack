#ifndef PAINTWIDGET_H
#define PAINTWIDGET_H

#include <QWidget>
#include <QPainter>
#include <QPaintEvent>
#include <QColor>

class PaintWidget: public QWidget
{
    Q_OBJECT;
public:
    PaintWidget(QWidget* parent = nullptr);

protected:
    void paintEvent(QPaintEvent* event) override;
};

#endif // PAINTWIDGET_H
