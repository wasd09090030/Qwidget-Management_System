#ifndef FINANCEWINDOW_H
#define FINANCEWINDOW_H

#include <QWidget>
#include <QTableView>
#include <QChartView>
#include <QDateEdit>
#include <QPushButton>
#include <QHBoxLayout>
#include <QVBoxLayout>
#include <QTableWidget>
#include "addinfodialog.h"
#include "paymentchart.h"

class FinanceWindow : public QWidget
{
    Q_OBJECT

public:
    explicit FinanceWindow(QWidget *parent = nullptr);
    void loadFinanceData();
    void onDeleteBtnClicked();
    void onAddBtnClicked();
    void onModifyBtnClicked();

private:
    AddInfoDialog *addFundDialog;
    // 顶部控件
    QDateEdit *startDateEdit;
    QDateEdit *endDateEdit;
    QPushButton *addBtn;
    QPushButton *deleteBtn;
    QPushButton *modifyBtn;

    // 中间控件
    QTableWidget *financeTableView;
    PaymentChart *chartView1;

    // 底部控件
    PaymentChart *chartView2;

    // 布局
    QHBoxLayout *topLayout;
    QHBoxLayout *middleLayout;
    QVBoxLayout *mainLayout;
};

#endif // FINANCEWINDOW_H
