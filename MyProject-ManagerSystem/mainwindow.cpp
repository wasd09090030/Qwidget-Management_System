#include "mainwindow.h"
#include "personalinfo.h"
#include "financewindow.h"
#include "settingswindow.h"

MainWindow::MainWindow(QWidget *parent)
    : QWidget(parent)
{
    // 设置主窗口大小
    this->resize(1200, 800);

    // 创建堆叠窗口
    stackedWidget = new QStackedWidget(this);
    stackedWidget->setMinimumSize(1000, 600);

    // 创建个人信息窗口
    PersonalInfo *personalInfo = new PersonalInfo(this);
    //创建财务信息窗口
    FinanceWindow *financeInfo = new FinanceWindow(this);
    //创建系统设置窗口
    SettingsWindow *settingsInfo = new SettingsWindow(this);

    // 将个人信息窗口添加到堆叠窗口
    stackedWidget->addWidget(personalInfo);
    stackedWidget->addWidget(financeInfo);
    stackedWidget->addWidget(settingsInfo);

    // 连接窗口大小改变信号
    connect(settingsInfo, &SettingsWindow::windowSizeChanged, this, [this](int width, int height) {
        this->resize(width, height);
    });

    // 创建按钮并设置大小
    personalInfoBtn = new QPushButton("个人信息", this);
    personalInfoBtn->setFixedSize(100, 80);
    financeBtn = new QPushButton("财务状况", this);
    financeBtn->setFixedSize(100, 80);
    settingsBtn = new QPushButton("系统设置", this);
    settingsBtn->setFixedSize(100, 80);

    // 设置按钮布局
    buttonLayout = new QVBoxLayout();
    buttonLayout->addWidget(personalInfoBtn);
    buttonLayout->addWidget(financeBtn);
    buttonLayout->addWidget(settingsBtn);
    buttonLayout->addStretch();

    // 设置主布局
    mainLayout = new QHBoxLayout(this);
    mainLayout->addLayout(buttonLayout);
    mainLayout->addWidget(stackedWidget, 1);

    // 连接信号槽
    connect(personalInfoBtn, &QPushButton::clicked, this, &MainWindow::switchToPersonalInfo);
    connect(financeBtn, &QPushButton::clicked, this, &MainWindow::switchToFinance);
    connect(settingsBtn, &QPushButton::clicked, this, &MainWindow::switchToSettings);
}

MainWindow::~MainWindow()
{
}

void MainWindow::switchToPersonalInfo()
{
    stackedWidget->setCurrentIndex(0);
}

void MainWindow::switchToFinance()
{
    stackedWidget->setCurrentIndex(1);
}


void MainWindow::switchToSettings()
{
    stackedWidget->setCurrentIndex(2);
}
