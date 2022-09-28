#include "Inc/myview.h"
#include <QScrollBar>
#include <math.h>

MyView::MyView()
{
    setDragMode(QGraphicsView::NoDrag);
    setTransformationAnchor( QGraphicsView::AnchorUnderMouse );
}

void MyView::wheelEvent(QWheelEvent *event)
{
    const QPointF p0scene = mapToScene(event->pos());

    qreal factor = std::pow(1.001, event->delta());
    scale(factor, factor);

    const QPointF move = mapFromScene(p0scene) - event->pos();
    qreal offsetX = move.x() + horizontalScrollBar()->value();
    qreal offsetY = move.y() + verticalScrollBar()->value();

    horizontalScrollBar()->setValue(offsetX);
    verticalScrollBar()->setValue(offsetY);
}

void MyView::mouseMoveEvent(QMouseEvent *event)
{
    //TODO: Реализовать построение пути по ведению мыши
}
