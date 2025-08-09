#include "firsttaskwidget.h"
#include <QLineEdit>
#include <QPushButton>
#include <QLabel>
#include <QVBoxLayout>
#include <QHBoxLayout>
#include <QString>
#include <QMessageBox>
#include "interpolator.h"
#include <sstream>
#include <QStackedWidget>

FirstTaskWidget::FirstTaskWidget(QWidget* parent) : QWidget(parent)
{
    auto* mainLayout = new QVBoxLayout(this);

    m_inputXs = new QLineEdit(this);
    m_inputYs = new QLineEdit(this);
    m_inputX = new QLineEdit(this);

    m_inputXs->setPlaceholderText("Введите значения X через пробел, например: 0 1 2 3");
    m_inputYs->setPlaceholderText("Введите значения Y через пробел, например: 0 2 4 6");
    m_inputX->setPlaceholderText("Введите X для интерполяции");

    m_btnCalculate = new QPushButton("Вычислить", this);
    m_btnBack = new QPushButton("Назад", this);

    m_labelResult = new QLabel(this);
    m_labelResult->setWordWrap(true);

    mainLayout->addWidget(m_inputXs);
    mainLayout->addWidget(m_inputYs);
    mainLayout->addWidget(m_inputX);
    mainLayout->addWidget(m_btnCalculate);
    mainLayout->addWidget(m_labelResult);
    mainLayout->addWidget(m_btnBack);

    connect(m_btnCalculate, &QPushButton::clicked, this, &FirstTaskWidget::onCalculateClicked);
    connect(m_btnBack, &QPushButton::clicked, this, &FirstTaskWidget::onBackClicked);
}

static std::vector<double> parseDoubles(const QString& text)
{
    std::vector<double> result;
    std::istringstream stream(text.toStdString());
    double val;
    while (stream >> val)
        result.push_back(val);
    return result;
}

void FirstTaskWidget::onCalculateClicked()
{
    try
    {
        auto xs = parseDoubles(m_inputXs->text());
        auto ys = parseDoubles(m_inputYs->text());
        bool ok;
        double x = m_inputX->text().toDouble(&ok);
        if (!ok)
        {
            QMessageBox::warning(this, "Ошибка", "Некорректное значение X");
            return;
        }

        Interpolator<double> interp(xs, ys);
        double y = interp.interpolate(x);

        m_labelResult->setText(QString("Результат интерполяции (экстраполяции): y = %1").arg(y));
    }
    catch (const std::exception& ex)
    {
        QMessageBox::warning(this, "Ошибка", ex.what());
    }
}

void FirstTaskWidget::onBackClicked()
{
    // Возвращаемся на главное меню
    QWidget* w = parentWidget();
    while (w && !qobject_cast<QStackedWidget*>(w)) {
        w = w->parentWidget();
    }
    if (auto stack = qobject_cast<QStackedWidget*>(w)) {
        stack->setCurrentIndex(0); // главный экран — индекс 0
    }
}
