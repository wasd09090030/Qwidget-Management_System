#include "dbmanager.h"
#include <QVariant>

DbManager::DbManager(const QString& path)
{
    m_db = QSqlDatabase::addDatabase("QSQLITE");
    m_db.setDatabaseName(path);

    if (!m_db.open()) {
        qDebug() << "Error: connection with database failed";
    } else {
        qDebug() << "Database: connection ok";
    }
}

DbManager::~DbManager()
{
    if (m_db.isOpen()) {
        m_db.close();
    }
}

bool DbManager::isOpen() const
{
    return m_db.isOpen();
}


//读取学生表中的所有数据
QList<QList<QVariant>> DbManager::getAllStudents()
{
    QList<QList<QVariant>> students;

    QSqlQuery query("SELECT * FROM students");
    while (query.next()) {
        QList<QVariant> student;
        for (int i = 0; i < 5; ++i) {
            student.append(query.value(i));
        }
        students.append(student);
    }

    return students;
}


QList<QList<QVariant>> DbManager::getAllFunds()
{
    QList<QList<QVariant>> funds;

    QSqlQuery query("SELECT * FROM MyManageFunds", m_db);

    while (query.next()) {
        QList<QVariant> fund;
        //使用 append() 或 << 运算符向Qlist添加值
        fund << query.value("id")
             << query.value("name")
             << query.value("money")
             << query.value("paymentMode")
             << query.value("payDate");
        funds.append(fund);
    }

    return funds;
}

//添加学生数据
bool DbManager::addStudent(const QList<QVariant>& studentData)
{
    if (!m_db.isOpen()) {
        qDebug() << "数据库未连接";
        return false;
    }

    QSqlQuery query;
    query.prepare("INSERT INTO students (id, name, age, score, target) VALUES (?, ?, ?, ?, ?)");

    for (int i = 0; i < studentData.size(); ++i) {
        query.addBindValue(studentData[i]);
    }

    if (!query.exec()) {
        qDebug() << "添加学生失败:" << query.lastError();
        return false;
    }

    return true;
}


//删除学生数据，使用id
bool DbManager::deleteStudent(int id)
{
    if (!m_db.isOpen()) {
        qDebug() << "数据库未连接";
        return false;
    }

    QSqlQuery query;
    query.prepare("DELETE FROM students WHERE id = ?");
    query.addBindValue(id);

    if (!query.exec()) {
        qDebug() << "删除学生失败:" << query.lastError();
        return false;
    }

    return query.numRowsAffected() > 0;
}

bool DbManager::deleteFund(int id)
{
    if (!m_db.isOpen()) {
        qDebug() << "数据库未连接";
        return false;
    }

    QSqlQuery query;
    query.prepare("DELETE FROM MyManageFunds WHERE id = ?");
    query.addBindValue(id);

    if (!query.exec()) {
        qDebug() << "删除资金记录失败:" << query.lastError();
        return false;
    }

    return query.numRowsAffected() > 0;
}

bool DbManager::addFund(const QList<QVariant>& fundData)
{
    if (!m_db.isOpen()) {
        qDebug() << "数据库未连接";
        return false;
    }

    QSqlQuery query;
    query.prepare("INSERT INTO MyManageFunds (id, name, money, paymentMode, payDate) VALUES (?, ?, ?, ?, ?)");

    for (int i = 0; i < fundData.size(); ++i) {
        query.addBindValue(fundData[i]);
    }

    if (!query.exec()) {
        qDebug() << "添加资金记录失败:" << query.lastError();
        return false;
    }

    return true;
}

bool DbManager::updateFund(int id, const QList<QVariant>& fundData)
{
    if (!m_db.isOpen()) {
        qDebug() << "数据库未连接";
        return false;
    }

    QSqlQuery query;
    query.prepare("UPDATE MyManageFunds SET name = ?, money = ?, paymentMode = ?, payDate = ? WHERE id = ?");

    //从下标1开始插入
    for (int i = 1; i < fundData.size(); ++i) {
        query.addBindValue(fundData[i]);
    }
    query.addBindValue(id);

    if (!query.exec()) {
        qDebug() << "更新资金记录失败:" << query.lastError();
        return false;
    }

    return query.numRowsAffected() > 0;
}

bool DbManager::verifyUser(const QString &name, const QString &password)
{
    QSqlQuery query;
    query.prepare("SELECT * FROM user WHERE name = :name AND password = :password");

    //替换值
    query.bindValue(":name", name);
    query.bindValue(":password", password);

    if (!query.exec()) {
        qDebug() << "验证用户失败:" << query.lastError();
        return false;
    }

    return query.next();
}

bool DbManager::insertUser(const QString& name, const QString& password)
{
    if (!m_db.isOpen()) {
        qDebug() << "数据库未连接";
        return false;
    }

    // 检查用户名是否已存在
    QSqlQuery checkQuery;
    checkQuery.prepare("SELECT name FROM user WHERE name = ?");
    checkQuery.addBindValue(name);

    if (!checkQuery.exec()) {
        qDebug() << "检查用户名失败:" << checkQuery.lastError();
        return false;
    }

    if (checkQuery.next()) {
        qDebug() << "用户名已存在";
        return false;
    }

    // 插入新用户
    QSqlQuery insertQuery;
    insertQuery.prepare("INSERT INTO user (name, password) VALUES (?, ?)");
    insertQuery.addBindValue(name);
    insertQuery.addBindValue(password);

    if (!insertQuery.exec()) {
        qDebug() << "插入用户失败:" << insertQuery.lastError();
        return false;
    }

    return true;
}
