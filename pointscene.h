#ifndef POINTSCENE_H
#define POINTSCENE_H

#include <QGraphicsScene>
#include <QGraphicsSceneMouseEvent>
#include <QPointF>
#include <vector>

class PointScene : public QGraphicsScene
{
    Q_OBJECT

public:
    explicit PointScene(QObject *parent = nullptr);
    std::vector<QPointF> points;

protected:
    void mouseDoubleClickEvent(QGraphicsSceneMouseEvent *event) override;
};

#endif // POINTSCENE_H
