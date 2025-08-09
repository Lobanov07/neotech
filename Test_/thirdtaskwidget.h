#pragma once
#include <QWidget>
#include <QImage>
#include <QPolygon>
#include <QVector>

class QPushButton;

class ThirdTaskWidget : public QWidget
{
    Q_OBJECT
public:
    explicit ThirdTaskWidget(QWidget* parent = nullptr);

    void loadImage(const QString& path);

signals:
    void backToMenu();

protected:
    void paintEvent(QPaintEvent*) override;
    void mousePressEvent(QMouseEvent* event) override;
    void mouseMoveEvent(QMouseEvent* event) override;
    void mouseReleaseEvent(QMouseEvent* event) override;

private:
    QImage m_image;
    QVector<QPolygon> m_polygons;  // Список всех полигонов
    QPolygon m_currentPolygon;     // Текущий рисуемый полигон

    bool m_draggingVertex = false;
    bool m_draggingPolygon = false;
    int m_dragPolygonIndex = -1;
    int m_dragVertexIndex = -1;
    QPoint m_lastMousePos;

    QPushButton* m_backButton;
};
