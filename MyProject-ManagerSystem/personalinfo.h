#ifndef PERSONALINFO_H
#define PERSONALINFO_H

#include <QWidget>
#include <QTableWidget>
#include<QPushButton>
#include<QVBoxLayout>
#include<QHBoxLayout>
#include "addinfodialog.h"

class PersonalInfo : public QWidget
{
    Q_OBJECT

public:
    explicit PersonalInfo(QWidget *parent = nullptr);
    void loadDataFromDatabase();
    void onAddBtnClicked();

private:
    QTableWidget *personalInfoTable;
    QPushButton *addInfoBtn;
    QPushButton *deleteInfoBtn;
    QPushButton *updateTableBtn;
    AddInfoDialog *addInfoDialog;
};

#endif // PERSONALINFO_H
