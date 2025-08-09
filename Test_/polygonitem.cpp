#include "polygonitem.h"
#include "vertexhandle.h"

#include <QPen>
#include <QBrush>

PolygonItem::PolygonItem(const QPolygonF& polygon, QGraphicsItem* parent)
    : QGraphicsPolygonItem(polygon, parent)
{
    setPen(QPen(Qt::red, 2));
    setBrush(QColor(255, 0, 0, 50));
    setFlags(QGraphicsItem::ItemIsSelectable | QGraphicsItem::ItemIsMovable);

    for (int i = 0; i < polygon.size(); ++i) {
        auto handle = new VertexHandle(polygon[i], this);
        m_handles.append(handle);
    }
}

void PolygonItem::updatePolygon()
{
    QPolygonF poly;
    for (auto h : m_handles) {
        poly << h->pos();
    }
    setPolygon(poly);
}
