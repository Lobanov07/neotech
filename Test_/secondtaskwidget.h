#pragma once

#include <QWidget>
#include <QListWidget>
#include <QPushButton>
#include <QLineEdit>
#include <QComboBox>
#include <QLabel>
#include <QVBoxLayout>
#include <memory>
#include <vector>
#include "shapes.h"

class SecondTaskWidget : public QWidget
{
    Q_OBJECT
public:
    explicit SecondTaskWidget(QWidget *parent = nullptr);

signals:
    void backToMenu();

private slots:
    void addShape();
    void calculateArea();
    void shapeTypeChanged(const QString&);

private:
    QListWidget* m_shapeList;
    QPushButton* m_btnAdd;
    QPushButton* m_btnCalculate;
    QPushButton* m_btnBack;


    QComboBox* m_shapeSelector;
    QLineEdit* m_radiusEdit;      // для Circle
    QLineEdit* m_widthEdit;       // для Rectangle
    QLineEdit* m_heightEdit;      // для Rectangle
    QLineEdit* m_colorEdit;

    std::vector<std::shared_ptr<Shape>> m_shapes;

    void updateInputsVisibility();
};
