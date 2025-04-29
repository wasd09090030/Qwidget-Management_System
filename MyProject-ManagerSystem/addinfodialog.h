#ifndef ADDINFODIALOG_H
#define ADDINFODIALOG_H

#include <QDialog>
#include <QLineEdit>
#include <QFormLayout>
#include <QDialogButtonBox>
#include <QVariant>

class AddInfoDialog : public QDialog
{
    Q_OBJECT

public:
    enum DialogType {
        PersonalInfoType,
        FinanceType
    };

    explicit AddInfoDialog(DialogType type, QWidget *parent = nullptr);
    explicit AddInfoDialog(QWidget *parent = nullptr); // 默认构造函数，用于PersonalInfo

    QList<QVariant> getStudentData() const;
    QList<QVariant> getFundData() const;

    // 财务信息字段
    QLineEdit *fundIdEdit;
    QLineEdit *fundNameEdit;
    QLineEdit *amountEdit;
    QLineEdit *paymentMethodEdit;
    QLineEdit *paymentDateEdit;

    DialogType m_type;

private:
    void setupPersonalInfoUI();
    void setupFinanceUI();

    // 个人信息字段
    QLineEdit *idEdit;
    QLineEdit *nameEdit;
    QLineEdit *ageEdit;
    QLineEdit *scoreEdit;
    QLineEdit *goalEdit;


};

#endif // ADDINFODIALOG_H
