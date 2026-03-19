#include "pointscene.h"
#include <QGraphicsEllipseItem>

PointScene::PointScene(QObject *parent)
    : QGraphicsScene{parent}
{}

void PointScene::mouseDoubleClickEvent(QGraphicsSceneMouseEvent *event){
    QPointF pos = event->scenePos();
    points.push_back(pos);
    addEllipse(pos.x()-2, pos.y()-2,4,4,QPen(Qt::white), QBrush(Qt::white));
    QGraphicsScene::mouseDoubleClickEvent(event);
}