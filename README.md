# Qwidget-Management_System
学习QT后练手的一个项目<br>
使用QWidget写的后台管理系统，主要使用了QWidget，数据库sqlite，通过模块化设计给不同的页面添加不同的功能。

# Qt 6 框架
- 使用了 Qt 的核心模块（如 `QWidget`、`QDialog`、`QPushButton`、`QVBoxLayout`、`QHBoxLayout`、`QTableWidget`、`QComboBox`、`QTextEdit`、`QCheckBox` 等），用于实现窗口界面、布局、控件和信号槽机制。
- 代码中包含了 Qt 的信号与槽（signals/slots）机制，例如：  
  `void windowSizeChanged(int width, int height);`

# C++ 编程语言
- 所有业务逻辑和界面实现均采用 C++ 编写

# 数据库支持
- 登录窗口 `LoginDialog` 中有 `DbManager db;`，并且通过 `db.verifyUser` 和 `db.insertUser` 进行用户验证和注册，集成了数据库（如 SQLite）用于用户信息管理。

# 模块化设计
- 项目结构分为以下模块：
  - 主窗口（`MainWindow`）
  - 个人信息（`PersonalInfo`）
  - 财务信息（`FinanceWindow`）
  - 系统设置（`SettingsWindow`）  
  便于维护和扩展。

# 图表与数据可视化
- `FinanceWindow` 中引用了 `QChartView` 和自定义的 `PaymentChart`，用于财务数据的图表展示。
