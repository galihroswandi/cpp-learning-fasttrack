#include "GraphicsView.h"

#include <QWheelEvent>
#include <QMouseEvent>

GraphicsView::GraphicsView(QWidget* parent)
    : QGraphicsView(parent),
      currentScale(1.0),
      dragging(false) {
    setRenderHint(QPainter::Antialiasing);
    setDragMode(QGraphicsView::NoDrag);
    setTransformationAnchor(QGraphicsView::AnchorUnderMouse);
    setViewportUpdateMode(QGraphicsView::SmartViewportUpdate);
}

void GraphicsView::setZoom(int percent) {
    qreal targetScale = percent / 100.0;
    if (targetScale <= 0.0)
        return;

    resetTransform();
    scale(targetScale, targetScale);
    currentScale = targetScale;
}

int GraphicsView::zoom() const {
    return static_cast<int>(currentScale * 100);
}

void GraphicsView::wheelEvent(QWheelEvent* event) {
    constexpr qreal factor = 1.15;
    if (event->angleDelta().y() > 0) {
        scale(factor, factor);
        currentScale *= factor;
    } else {
        scale(1.0 / factor, 1.0 / factor);
        currentScale /= factor;
    }
    event->accept();
}

void GraphicsView::mousePressEvent(QMouseEvent* event) {
    if (event->button() == Qt::LeftButton) {
        dragging = true;
        lastDragPos = event->pos();
        setCursor(Qt::ClosedHandCursor);
    }
    QGraphicsView::mousePressEvent(event);
}

void GraphicsView::mouseMoveEvent(QMouseEvent* event) {
    if (dragging) {
        QPoint delta = event->pos() - lastDragPos;
        lastDragPos = event->pos();
        horizontalScrollBar()->setValue(horizontalScrollBar()->value() - delta.x());
        verticalScrollBar()->setValue(verticalScrollBar()->value() - delta.y());
    }
    QGraphicsView::mouseMoveEvent(event);
}

void GraphicsView::mouseReleaseEvent(QMouseEvent* event) {
    if (event->button() == Qt::LeftButton) {
        dragging = false;
        setCursor(Qt::ArrowCursor);
    }
    QGraphicsView::mouseReleaseEvent(event);
}
