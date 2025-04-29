#include "personalinfo.h"
#include "dbmanager.h"
#include <QDialog>
#include <QFormLayout>
#include <QLineEdit>
#include <QDialogButtonBox>


PersonalInfo::PersonalInfo(QWidget *parent)
    : QWidget(parent)
{
    personalInfoTable = new QTableWidget(8, 5, this);
    personalInfoTable->setHorizontalHeaderLabels({"ID", "姓名", "年龄", "成绩", "目标"});

    // 设置列宽
    personalInfoTable->setColumnWidth(0, 150);
    personalInfoTable->setColumnWidth(1, 150);
    personalInfoTable->setColumnWidth(2, 150);
    personalInfoTable->setColumnWidth(3, 150);
    personalInfoTable->setColumnWidth(4, 150);

    // 设置行高
    for(int i = 0; i < personalInfoTable->rowCount(); ++i) {
        personalInfoTable->setRowHeight(i, 50);
    }

    // 创建按钮
    addInfoBtn = new QPushButton("添加个人信息", this);
    deleteInfoBtn = new QPushButton("删除个人信息", this);

    // 设置按钮大小
    addInfoBtn->setFixedSize(100, 60);
    deleteInfoBtn->setFixedSize(100, 60);

    // 创建右侧按钮布局
    QVBoxLayout *buttonLayout = new QVBoxLayout();
    buttonLayout->addWidget(addInfoBtn);
    buttonLayout->addWidget(deleteInfoBtn);
    buttonLayout->addStretch();

    // 创建主布局
    QHBoxLayout *mainLayout = new QHBoxLayout(this);
    mainLayout->addWidget(personalInfoTable, 1);
    mainLayout->addLayout(buttonLayout);

    // 连接数据库并加载数据
    loadDataFromDatabase();

    // 连接按钮信号与槽
    //添加个人信息的实现
    connect(addInfoBtn, &QPushButton::clicked, this, &PersonalInfo::onAddBtnClicked);


    //删除个人信息的实现
    connect(deleteInfoBtn, &QPushButton::clicked, this, [this]() {
        int currentRow = personalInfoTable->currentRow();
        if (currentRow >= 0) {
            QTableWidgetItem *idItem = personalInfoTable->item(currentRow, 0);
            if (idItem) {
                DbManager db("E:\\database\\manage.db");
                if (db.isOpen()) {
                    db.deleteStudent(idItem->text().toInt());
                    loadDataFromDatabase();
                }
            }
        }
    });
}

void PersonalInfo::loadDataFromDatabase()
{
    DbManager db("E:\\database\\manage.db");
    if (!db.isOpen()) {
        qDebug() << "无法打开数据库";
        return;
    }

    QList<QList<QVariant>> students = db.getAllStudents();

    personalInfoTable->setRowCount(0);
    personalInfoTable->setRowCount(students.size());

    for (int row = 0; row < students.size(); ++row) {
        const QList<QVariant>& student = students[row];
        for (int col = 0; col < student.size(); ++col) {
            QTableWidgetItem *item = new QTableWidgetItem(student[col].toString());
            personalInfoTable->setItem(row, col, item);
        }
    }
}

void PersonalInfo::onAddBtnClicked()
{
    AddInfoDialog dialog(this);
    if (dialog.exec() == QDialog::Accepted) {
        DbManager db("E:\\database\\manage.db");
        if (db.addStudent(dialog.getStudentData())) {
            loadDataFromDatabase();
        }
    }
}

