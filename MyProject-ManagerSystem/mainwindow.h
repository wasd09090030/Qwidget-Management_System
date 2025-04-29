#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QWidget>
#include <QStackedWidget>
#include <QPushButton>
#include <QVBoxLayout>
#include <QHBoxLayout>


class MainWindow : public QWidget
{
    Q_OBJECT

public:
    MainWindow(QWidget *parent = nullptr);
    ~MainWindow();

private:
    QStackedWidget *stackedWidget;
    QPushButton *personalInfoBtn;
    QPushButton *financeBtn;
    QPushButton *settingsBtn;
    QVBoxLayout *buttonLayout;
    QHBoxLayout *mainLayout;

private slots:
    void switchToPersonalInfo();
    void switchToFinance();
    void switchToSettings();
};

#endif // MAINWINDOW_H
