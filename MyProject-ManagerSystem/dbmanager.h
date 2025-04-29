#ifndef DBMANAGER_H
#define DBMANAGER_H

#include <QString>
#include <QSqlDatabase>
#include <QSqlQuery>
#include <QSqlError>
#include <QDebug>

class DbManager
{
public:
    explicit DbManager(const QString& path);
    ~DbManager();

    bool isOpen() const;
    QList<QList<QVariant>> getAllStudents();

    //QVariant，Qt 提供的一个通用数据类型，可以存储多种不同类型的值（如 int、QString、QDate、bool 等）
    bool addStudent(const QList<QVariant>& studentData);
    QList<QList<QVariant>> getAllFunds();
    bool deleteStudent(int id);

    bool deleteFund(int id);
    bool addFund(const QList<QVariant>& fundData);
    bool updateFund(int id, const QList<QVariant>& fundData);

    bool verifyUser(const QString &name, const QString &password);
    bool insertUser(const QString& name, const QString& password);

private:
    QSqlDatabase m_db;
};

#endif // DBMANAGER_H
