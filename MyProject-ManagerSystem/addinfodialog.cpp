#include "addinfodialog.h"
#include <QVBoxLayout>

//构造函数。根据调用的类来实现不同的dialog窗口
AddInfoDialog::AddInfoDialog(DialogType type, QWidget *parent)
    : QDialog(parent), m_type(type)
{
    if (type == PersonalInfoType) {
        setupPersonalInfoUI();
    } else {
        setupFinanceUI();
    }
}

//默认构造函数，不实现
AddInfoDialog::AddInfoDialog(QWidget *parent)
    : AddInfoDialog(PersonalInfoType, parent)
{
}

//添加个人信息需要的
void AddInfoDialog::setupPersonalInfoUI()
{
    setWindowTitle("个人信息");
    setFixedSize(300, 200);

    QFormLayout *formLayout = new QFormLayout(this);

    idEdit = new QLineEdit(this);
    nameEdit = new QLineEdit(this);
    ageEdit = new QLineEdit(this);
    scoreEdit = new QLineEdit(this);
    goalEdit = new QLineEdit(this);

    formLayout->addRow("ID", idEdit);
    formLayout->addRow("姓名", nameEdit);
    formLayout->addRow("年龄", ageEdit);
    formLayout->addRow("成绩", scoreEdit);
    formLayout->addRow("目标", goalEdit);

    QDialogButtonBox *buttonBox = new QDialogButtonBox(
        QDialogButtonBox::Ok | QDialogButtonBox::Cancel,
        Qt::Horizontal, this);
    formLayout->addRow(buttonBox);

    connect(buttonBox, &QDialogButtonBox::accepted, this, &QDialog::accept);
    connect(buttonBox, &QDialogButtonBox::rejected, this, &QDialog::reject);
}

//添加财务信息
void AddInfoDialog::setupFinanceUI()
{
    setWindowTitle("财务信息");
    setFixedSize(400, 250);

    QFormLayout *formLayout = new QFormLayout(this);

    fundIdEdit = new QLineEdit(this);
    fundNameEdit = new QLineEdit(this);
    amountEdit = new QLineEdit(this);
    paymentMethodEdit = new QLineEdit(this);
    paymentDateEdit = new QLineEdit(this);

    formLayout->addRow("ID", fundIdEdit);
    formLayout->addRow("姓名", fundNameEdit);
    formLayout->addRow("金额", amountEdit);
    formLayout->addRow("支付方式", paymentMethodEdit);
    formLayout->addRow("支付日期", paymentDateEdit);

    QDialogButtonBox *buttonBox = new QDialogButtonBox(
        QDialogButtonBox::Ok | QDialogButtonBox::Cancel,
        Qt::Horizontal, this);
    formLayout->addRow(buttonBox);

    connect(buttonBox, &QDialogButtonBox::accepted, this, &QDialog::accept);
    connect(buttonBox, &QDialogButtonBox::rejected, this, &QDialog::reject);
}

QList<QVariant> AddInfoDialog::getStudentData() const
{
    return {
        idEdit->text(),
        nameEdit->text(),
        ageEdit->text().toInt(),
        scoreEdit->text().toDouble(),
        goalEdit->text()
    };
}

QList<QVariant> AddInfoDialog::getFundData() const
{
    return {
        fundIdEdit->text(),
        fundNameEdit->text(),
        amountEdit->text().toDouble(),
        paymentMethodEdit->text(),
        paymentDateEdit->text()
    };
}
