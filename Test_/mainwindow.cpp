#include "mainwindow.h"
#include <QFileDialog>
#include <QPushButton>
#include <QStackedWidget>
#include <QVBoxLayout>

MainWindow::MainWindow(QWidget* parent) : QMainWindow(parent)
{
    m_stack = new QStackedWidget(this);

    m_mainMenuWidget = createMainMenu();
    m_firstTaskWidget = new FirstTaskWidget(this);
    m_secondTaskWidget = new SecondTaskWidget(this);
    m_thirdTaskWidget  = new ThirdTaskWidget(this);

    m_stack->addWidget(m_mainMenuWidget);
    m_stack->addWidget(m_firstTaskWidget);
    m_stack->addWidget(m_secondTaskWidget);
    m_stack->addWidget(m_thirdTaskWidget);

    setCentralWidget(m_stack);
    m_stack->setCurrentWidget(m_mainMenuWidget);
    resize(800, 600);

    // Кнопки главного меню
    connect(static_cast<QPushButton*>(m_mainMenuWidget->findChild<QPushButton*>("btnFirst")),  &QPushButton::clicked,
            this, &MainWindow::showFirstTask);

    connect(static_cast<QPushButton*>(m_mainMenuWidget->findChild<QPushButton*>("btnSecond")), &QPushButton::clicked,
            this, &MainWindow::showSecondTask);

    connect(static_cast<QPushButton*>(m_mainMenuWidget->findChild<QPushButton*>("btnThird")),  &QPushButton::clicked,
            this, &MainWindow::showThirdTask);

    // Возврат в меню
    connect(m_secondTaskWidget, &SecondTaskWidget::backToMenu, this, &MainWindow::showMainMenu);
    connect(m_thirdTaskWidget,  &ThirdTaskWidget::backToMenu,  this, &MainWindow::showMainMenu);
}

QWidget* MainWindow::createMainMenu()
{
    QWidget* widget = new QWidget(this);
    QVBoxLayout* layout = new QVBoxLayout(widget);
    layout->setSpacing(20);         // расстояние между кнопками
    layout->setContentsMargins(50, 50, 50, 50); // отступы вокруг

    QPushButton* btnFirst = new QPushButton("Первое задание", widget);
    btnFirst->setObjectName("btnFirst");
    btnFirst->setSizePolicy(QSizePolicy::Expanding, QSizePolicy::Expanding);
    btnFirst->setMinimumHeight(60);

    QPushButton* btnSecond = new QPushButton("Второе задание", widget);
    btnSecond->setObjectName("btnSecond");
    btnSecond->setSizePolicy(QSizePolicy::Expanding, QSizePolicy::Expanding);
    btnSecond->setMinimumHeight(60);

    QPushButton* btnThird = new QPushButton("Третье задание", widget);
    btnThird->setObjectName("btnThird");
    btnThird->setSizePolicy(QSizePolicy::Expanding, QSizePolicy::Expanding);
    btnThird->setMinimumHeight(60);

    layout->addWidget(btnFirst);
    layout->addWidget(btnSecond);
    layout->addWidget(btnThird);

    widget->setLayout(layout);
    return widget;
}

void MainWindow::showFirstTask()
{
    m_stack->setCurrentWidget(m_firstTaskWidget);
}

void MainWindow::showSecondTask()
{
    m_stack->setCurrentWidget(m_secondTaskWidget);
}

void MainWindow::showThirdTask()
{
    QString fileName = QFileDialog::getOpenFileName(this, "Выберите изображение", "", "Images (*.png *.jpg *.bmp)");
    if (!fileName.isEmpty()) {
        m_thirdTaskWidget->loadImage(fileName);
        m_stack->setCurrentWidget(m_thirdTaskWidget);
        adjustSize();
    }
}

void MainWindow::showMainMenu()
{
    m_stack->setCurrentWidget(m_mainMenuWidget);
}
