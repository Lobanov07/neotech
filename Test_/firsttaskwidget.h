#pragma once
#include <QWidget>

class QLineEdit;
class QPushButton;
class QLabel;

class FirstTaskWidget : public QWidget
{
    Q_OBJECT
public:
    explicit FirstTaskWidget(QWidget* parent = nullptr);

private slots:
    void onCalculateClicked();
    void onBackClicked();

private:
    QLineEdit* m_inputXs;
    QLineEdit* m_inputYs;
    QLineEdit* m_inputX;

    QPushButton* m_btnCalculate;
    QPushButton* m_btnBack;

    QLabel* m_labelResult;
};
