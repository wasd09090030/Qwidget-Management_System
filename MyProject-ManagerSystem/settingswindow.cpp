#include "settingswindow.h"


SettingsWindow::SettingsWindow(QWidget *parent) : QWidget(parent)
{
    // 创建分辨率选择下拉菜单
    resolutionComboBox = new QComboBox(this);
    resolutionComboBox->addItem("800x600");
    resolutionComboBox->addItem("1000x800");
    resolutionComboBox->addItem("1200x900");

    // 创建功能说明文本框
    infoTextEdit = new QTextEdit(this);
    infoTextEdit->setReadOnly(true);
    infoTextEdit->setFixedSize(500, 300);
    infoTextEdit->setText("个人信息页面: 显示用户基本信息\n财务状况页面: 显示财务数据和图表\n系统设置页面: 调整窗口大小和查看功能说明");

    // 创建应用按钮
    applyBtn = new QPushButton("应用", this);


    // 设置布局
    mainLayout = new QVBoxLayout(this);
    mainLayout->addWidget(resolutionComboBox);
    mainLayout->addWidget(applyBtn);
    mainLayout->addWidget(infoTextEdit);


    // 连接信号槽
    connect(applyBtn, &QPushButton::clicked, this, [this]() {
        QString resolution = resolutionComboBox->currentText();
        QStringList dimensions = resolution.split('x');
        emit windowSizeChanged(dimensions[0].toInt(), dimensions[1].toInt());
    });
}
