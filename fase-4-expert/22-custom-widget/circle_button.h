#ifndef CIRCLE_BUTTON_H
#define CIRCLE_BUTTON_H

#include <QWidget>
#include <QPainter>
#include <QColor>

class CircleButton: public QWidget
{
    Q_OBJECT;

public:
    CircleButton(const QString& text, QColor color, QWidget* parent = nullptr);
    QSize sizeHint() const override;

signals:
    void clicked();

protected:
    void paintEvent(QPaintEvent* event) override;
    void enterEvent(QEnterEvent* event) override;
    void leaveEvent(QEvent* event) override;
    void mousePressEvent(QMouseEvent* event) override;
    void mouseReleaseEvent(QMouseEvent* event) override;

private:
    QString text;
    bool hovered;
    bool pressed;
    QColor customColor;
};

#endif // CIRCLE_BUTTON_H
