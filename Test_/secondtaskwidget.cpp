#include "secondtaskwidget.h"
#include <QHBoxLayout>
#include <QMessageBox>

SecondTaskWidget::SecondTaskWidget(QWidget *parent) : QWidget(parent)
{
    auto mainLayout = new QVBoxLayout(this);

    // Список фигур
    m_shapeList = new QListWidget(this);
    mainLayout->addWidget(m_shapeList);

    // Форма выбора фигуры и параметров
    auto formLayout = new QHBoxLayout();

    m_shapeSelector = new QComboBox(this);
    m_shapeSelector->addItems({"Shape", "Circle", "Rectangle"});
    formLayout->addWidget(m_shapeSelector);

    m_radiusEdit = new QLineEdit(this);
    m_radiusEdit->setPlaceholderText("Радиус");
    formLayout->addWidget(m_radiusEdit);

    m_widthEdit = new QLineEdit(this);
    m_widthEdit->setPlaceholderText("Ширина");
    formLayout->addWidget(m_widthEdit);

    m_heightEdit = new QLineEdit(this);
    m_heightEdit->setPlaceholderText("Высота");
    formLayout->addWidget(m_heightEdit);

    m_colorEdit = new QLineEdit(this);
    m_colorEdit->setPlaceholderText("Цвет");
    formLayout->addWidget(m_colorEdit);

    mainLayout->addLayout(formLayout);

    m_btnAdd = new QPushButton("Добавить фигуру", this);
    m_btnCalculate = new QPushButton("Посчитать площадь", this);
    m_btnBack = new QPushButton("Назад", this);

    mainLayout->addWidget(m_btnAdd);
    mainLayout->addWidget(m_btnCalculate);
    mainLayout->addWidget(m_btnBack);

    // Изначально показываем только цвет (для Shape), прячем радиус, ширину, высоту
    updateInputsVisibility();

    connect(m_shapeSelector, &QComboBox::currentTextChanged, this, &SecondTaskWidget::shapeTypeChanged);
    connect(m_btnAdd, &QPushButton::clicked, this, &SecondTaskWidget::addShape);
    connect(m_btnCalculate, &QPushButton::clicked, this, &SecondTaskWidget::calculateArea);
    connect(m_btnBack, &QPushButton::clicked, this, &SecondTaskWidget::backToMenu);

}

void SecondTaskWidget::updateInputsVisibility()
{
    QString type = m_shapeSelector->currentText();
    m_radiusEdit->setVisible(type == "Circle");
    m_widthEdit->setVisible(type == "Rectangle");
    m_heightEdit->setVisible(type == "Rectangle");
}

void SecondTaskWidget::shapeTypeChanged(const QString&)
{
    updateInputsVisibility();
}

void SecondTaskWidget::addShape()
{
    QString type = m_shapeSelector->currentText();
    QString color = m_colorEdit->text().trimmed();
    if (color.isEmpty()) color = "black";

    try
    {
        if (type == "Shape")
        {
            m_shapes.push_back(std::make_shared<Shape>(color.toStdString()));
            m_shapeList->addItem(QString::fromStdString("Shape, цвет: ") + color);
        }
        else if (type == "Circle")
        {
            bool ok = false;
            double r = m_radiusEdit->text().toDouble(&ok);
            if (!ok || r <= 0)
            {
                QMessageBox::warning(this, "Ошибка", "Введите корректный положительный радиус");
                return;
            }
            auto circle = std::make_shared<Circle>(r, color.toStdString());
            m_shapes.push_back(circle);
            m_shapeList->addItem(QString("Circle, радиус: %1, цвет: %2").arg(r).arg(color));
        }
        else if (type == "Rectangle")
        {
            bool okW = false, okH = false;
            double w = m_widthEdit->text().toDouble(&okW);
            double h = m_heightEdit->text().toDouble(&okH);
            if (!okW || w <= 0 || !okH || h <= 0)
            {
                QMessageBox::warning(this, "Ошибка", "Введите корректные положительные ширину и высоту");
                return;
            }
            auto rect = std::make_shared<Rectangle>(w, h, color.toStdString());
            m_shapes.push_back(rect);
            m_shapeList->addItem(QString("Rectangle, ширина: %1, высота: %2, цвет: %3").arg(w).arg(h).arg(color));
        }
    }
    catch (...)
    {
        QMessageBox::warning(this, "Ошибка", "Ошибка при создании фигуры");
    }
}

void SecondTaskWidget::calculateArea()
{
    double sum = CalcSumArea(m_shapes);
    QMessageBox::information(this, "Результат", QString("Суммарная площадь: %1").arg(sum));
}
