#include "circle_button.h"
#include <QMouseEvent>

CircleButton::CircleButton(const QString& text, QColor color, QWidget* parent): QWidget(parent), text(text), hovered(false), pressed(false), customColor(color)
{
    setCursor(Qt::PointingHandCursor);
    setMouseTracking(true);
}

QSize CircleButton::sizeHint() const
{
    return QSize(120, 120);
}

void CircleButton::paintEvent(QPaintEvent* event)
{
    QPainter painter(this);
    painter.setRenderHint(QPainter::Antialiasing);

    QColor bgColor = customColor;
    if(pressed) bgColor = customColor.darker(140);
    else if(hovered) bgColor = customColor.lighter(120);

    int size = qMin(width(), height()) - 4;
    int x = (width() - size) / 2;
    int y = (height() - size) / 2;

    painter.setPen(Qt::NoPen);
    painter.setBrush(bgColor);
    painter.drawEllipse(x, y, size, size);

    painter.setPen(Qt::white);
    painter.setFont(QFont("Arial", 12, QFont::Bold));
    painter.drawText(rect(), Qt::AlignCenter, text);
}

void CircleButton::enterEvent(QEnterEvent* event)
{
    hovered = true;
    pressed = false;
    update();
    QWidget::enterEvent(event);
    setCursor(Qt::ForbiddenCursor);
}

void CircleButton::leaveEvent(QEvent* event)
{
    hovered = false;
    pressed = false;
    update();
    QWidget::leaveEvent(event);
    setCursor(Qt::PointingHandCursor);
}

void CircleButton::mousePressEvent(QMouseEvent* event)
{
    if(event->button() == Qt::LeftButton)
    {
        pressed = true;
        update();
    }
    QWidget::mousePressEvent(event);
}

void CircleButton::mouseReleaseEvent(QMouseEvent* event)
{
    if(event->button() == Qt::LeftButton && pressed)
    {
        pressed = false;
        update();
        emit clicked();
    }
    QWidget::mouseReleaseEvent(event);
}