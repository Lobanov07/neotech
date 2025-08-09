#include "thirdtaskwidget.h"
#include <QPushButton>
#include <QVBoxLayout>
#include <QMouseEvent>
#include <QPainter>
#include <QFileDialog>

ThirdTaskWidget::ThirdTaskWidget(QWidget* parent)
    : QWidget(parent)
{
    QVBoxLayout* layout = new QVBoxLayout(this);

    m_backButton = new QPushButton("Назад", this);
    connect(m_backButton, &QPushButton::clicked, this, &ThirdTaskWidget::backToMenu);

    layout->addWidget(m_backButton);
    layout->setAlignment(m_backButton, Qt::AlignLeft | Qt::AlignTop);

    setMouseTracking(true);
}

void ThirdTaskWidget::loadImage(const QString& path)
{
    m_image.load(path);
    if (!m_image.isNull()) {
        const int maxWidth = 1200;   // максимальная ширина
        const int maxHeight = 800;   // максимальная высота

        QSize imgSize = m_image.size();

        if (imgSize.width() > maxWidth || imgSize.height() > maxHeight) {
            m_image = m_image.scaled(maxWidth, maxHeight, Qt::KeepAspectRatio, Qt::SmoothTransformation);
        }

        setFixedSize(m_image.size());
        update();
    }
    m_polygons.clear();
    m_currentPolygon.clear();
    update();
}

void ThirdTaskWidget::paintEvent(QPaintEvent*)
{
    QPainter p(this);

    if (!m_image.isNull())
        p.drawImage(0, 0, m_image);

    p.setRenderHint(QPainter::Antialiasing);
    p.setPen(QPen(Qt::red, 2));
    p.setBrush(Qt::NoBrush);

    // Нарисовать уже готовые полигоны
    for (const QPolygon& poly : m_polygons) {
        p.drawPolygon(poly);
        for (const QPoint& pt : poly)
            p.drawEllipse(pt, 4, 4);
    }

    // Рисуем текущий полигон
    if (!m_currentPolygon.isEmpty()) {
        p.drawPolyline(m_currentPolygon);
        for (const QPoint& pt : m_currentPolygon)
            p.drawEllipse(pt, 4, 4);
    }
}

void ThirdTaskWidget::mousePressEvent(QMouseEvent* event)
{
    if (event->button() == Qt::LeftButton) {
        // Проверка на захват вершины
        for (int i = 0; i < m_polygons.size(); ++i) {
            for (int j = 0; j < m_polygons[i].size(); ++j) {
                if (QLineF(event->pos(), m_polygons[i][j]).length() < 6) {
                    m_draggingVertex = true;
                    m_dragPolygonIndex = i;
                    m_dragVertexIndex = j;
                    return;
                }
            }
        }

        // Проверка на захват всего полигона
        for (int i = 0; i < m_polygons.size(); ++i) {
            if (m_polygons[i].boundingRect().contains(event->pos())) {
                m_draggingPolygon = true;
                m_dragPolygonIndex = i;
                m_lastMousePos = event->pos();
                return;
            }
        }

        // Если не попали в существующий полигон — рисуем новый
        m_currentPolygon << event->pos();
        update();
    }
    else if (event->button() == Qt::RightButton) {
        // Завершить текущий полигон
        if (m_currentPolygon.size() > 2) {
            m_polygons.append(m_currentPolygon);
            m_currentPolygon.clear();
            update();
        }
    }
}

void ThirdTaskWidget::mouseMoveEvent(QMouseEvent* event)
{
    if (m_draggingVertex && m_dragPolygonIndex >= 0 && m_dragVertexIndex >= 0) {
        m_polygons[m_dragPolygonIndex][m_dragVertexIndex] = event->pos();
        update();
    }
    else if (m_draggingPolygon && m_dragPolygonIndex >= 0) {
        QPoint delta = event->pos() - m_lastMousePos;
        m_lastMousePos = event->pos();
        for (QPoint& pt : m_polygons[m_dragPolygonIndex])
            pt += delta;
        update();
    }
}

void ThirdTaskWidget::mouseReleaseEvent(QMouseEvent*)
{
    m_draggingVertex = false;
    m_draggingPolygon = false;
    m_dragPolygonIndex = -1;
    m_dragVertexIndex = -1;
}
