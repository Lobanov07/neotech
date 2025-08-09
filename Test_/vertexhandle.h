#pragma once
#include <QGraphicsEllipseItem>
#include <QObject>

class PolygonItem;

class VertexHandle : public QObject, public QGraphicsEllipseItem
{
    Q_OBJECT
public:
    VertexHandle(QPointF pos, PolygonItem* parentPolygon);

signals:
    void moved();

protected:
    void mouseMoveEvent(QGraphicsSceneMouseEvent* event) override;

private:
    PolygonItem* m_parentPolygon;
};
