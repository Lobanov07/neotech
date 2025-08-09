#pragma once
#include <QMainWindow>
#include "firsttaskwidget.h"
#include "secondtaskwidget.h"
#include "thirdtaskwidget.h"

class QPushButton;
class QStackedWidget;

class MainWindow : public QMainWindow
{
    Q_OBJECT
public:
    explicit MainWindow(QWidget* parent = nullptr);

private slots:
    void showFirstTask();
    void showSecondTask();
    void showThirdTask();
    void showMainMenu();

private:
    QWidget* createMainMenu();

    QStackedWidget* m_stack;
    QWidget* m_mainMenuWidget;
    FirstTaskWidget* m_firstTaskWidget;
    SecondTaskWidget* m_secondTaskWidget;
    ThirdTaskWidget* m_thirdTaskWidget;
};
