#include "financewindow.h"
#include "dbmanager.h"

#include <QDate>

FinanceWindow::FinanceWindow(QWidget *parent)
    : QWidget(parent)
{
    DbManager db("E:\\database\\manage.db");

    // 加载数据到表格

    // 创建顶部控件
    startDateEdit = new QDateEdit(QDate::currentDate(), this);
    endDateEdit = new QDateEdit(QDate::currentDate(), this);
    addBtn = new QPushButton("添加", this);
    deleteBtn = new QPushButton("删除", this);
    modifyBtn = new QPushButton("修改", this);

    // 创建顶部布局
    topLayout = new QHBoxLayout();
    topLayout->addWidget(startDateEdit);
    topLayout->addWidget(endDateEdit);
    topLayout->addWidget(addBtn);
    topLayout->addWidget(deleteBtn);
    topLayout->addWidget(modifyBtn);

    // 创建中间控件
    financeTableView = new QTableWidget(this);
    financeTableView->setColumnCount(5);
    financeTableView->setHorizontalHeaderLabels(QStringList() << "ID" << "姓名" << "金额" << "支付方式" << "支付日期");
    chartView1 = new PaymentChart(this);

    // 创建中间布局
    middleLayout = new QHBoxLayout();
    middleLayout->addWidget(financeTableView, 6); // 60%宽度
    middleLayout->addWidget(chartView1, 4); // 40%宽度

    // 创建底部控件
    chartView2 = new PaymentChart(this);

    // 创建主布局
    mainLayout = new QVBoxLayout(this);
    mainLayout->addLayout(topLayout);
    mainLayout->addLayout(middleLayout,6);
    mainLayout->addWidget(chartView2,4); // 30%高度

    // 连接按钮信号槽
   connect(addBtn, &QPushButton::clicked, this, &FinanceWindow::onAddBtnClicked);
  connect(deleteBtn, &QPushButton::clicked, this, &FinanceWindow::onDeleteBtnClicked);
      connect(modifyBtn, &QPushButton::clicked, this, &FinanceWindow::onModifyBtnClicked);

    loadFinanceData();
}

void FinanceWindow::onAddBtnClicked()
{
    AddInfoDialog dialog(AddInfoDialog::FinanceType, this);
    if (dialog.exec() == QDialog::Accepted) {
        DbManager db("E:\\database\\manage.db");
        if (db.addFund(dialog.getFundData())) {
            loadFinanceData();
        }
    }
}

void FinanceWindow::onModifyBtnClicked()
{
    int row = financeTableView->currentRow();
    if (row >= 0) {
        AddInfoDialog dialog(AddInfoDialog::FinanceType, this);

        // 预填充当前选中行的数据
        dialog.fundIdEdit->setText(financeTableView->item(row, 0)->text());
        dialog.fundNameEdit->setText(financeTableView->item(row, 1)->text());
        dialog.amountEdit->setText(financeTableView->item(row, 2)->text());
        dialog.paymentMethodEdit->setText(financeTableView->item(row, 3)->text());
        dialog.paymentDateEdit->setText(financeTableView->item(row, 4)->text());

        if (dialog.exec() == QDialog::Accepted) {
            DbManager db("E:\\database\\manage.db");
            if (db.updateFund(financeTableView->item(row, 0)->text().toInt(), dialog.getFundData())) {
                loadFinanceData();
            }
        }
    }
}

void FinanceWindow::onDeleteBtnClicked()
{
    int row = financeTableView->currentRow();
    if (row >= 0) {
        DbManager db("E:\\database\\manage.db");
        if (db.deleteFund(financeTableView->item(row, 0)->text().toInt())) {
            loadFinanceData();
        }
    }
}

void FinanceWindow::loadFinanceData()
{
    DbManager db("E:\\database\\manage.db");
    if (!db.isOpen()) {
        qDebug() << "无法打开数据库";
        return;
    }

    QList<QList<QVariant>> funds = db.getAllFunds();

    financeTableView->clearContents();
    financeTableView->setRowCount(funds.size());

    for (int row = 0; row < funds.size(); ++row) {
        const QList<QVariant>& fund = funds[row];
        for (int col = 0; col < fund.size(); ++col) {
            QTableWidgetItem *item = new QTableWidgetItem(fund[col].toString());
            financeTableView->setItem(row, col, item);
        }
    }


    static_cast<PaymentChart*>(chartView1)->updateChart();
    static_cast<PaymentChart*>(chartView2)->updateLineChart();
}

