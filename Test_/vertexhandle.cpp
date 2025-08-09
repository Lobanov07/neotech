#include "vertexhandle.h"
#include "polygonitem.h"
#include <QGraphicsSceneMouseEvent>
#include <QBrush>

VertexHandle::VertexHandle(QPointF pos, PolygonItem* parentPolygon)
    : QGraphicsEllipseItem(-4, -4, 8, 8), m_parentPolygon(parentPolygon)
{
    setBrush(Qt::blue);
    setFlags(QGraphicsItem::ItemIsMovable | QGraphicsItem::ItemSendsGeometryChanges);
    setPos(pos);
    setParentItem(parentPolygon);
}

void VertexHandle::mouseMoveEvent(QGraphicsSceneMouseEvent* event)
{
    QGraphicsEllipseItem::mouseMoveEvent(event);
    m_parentPolygon->updatePolygon();
}
