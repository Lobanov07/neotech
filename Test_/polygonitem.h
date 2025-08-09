#pragma once
#include <QGraphicsPolygonItem>
#include <QObject>
#include <QList>

class VertexHandle;

class PolygonItem : public QObject, public QGraphicsPolygonItem
{
    Q_OBJECT
public:
    PolygonItem(const QPolygonF& polygon, QGraphicsItem* parent = nullptr);

    void updatePolygon();

private:
    QList<VertexHandle*> m_handles;
};
