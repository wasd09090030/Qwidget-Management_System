#include "logindialog.h"
#include <QSettings>
#include <QVBoxLayout>
#include <QLabel>
#include <QMessageBox>

LoginDialog::LoginDialog(QWidget *parent) : QDialog(parent), db("E:\\database\\manage.db")
{

    setWindowTitle("登录");
    setFixedSize(300, 200);

    QVBoxLayout *layout = new QVBoxLayout(this);

    QLabel *nameLabel = new QLabel("姓名:");
    nameEdit = new QLineEdit();
    layout->addWidget(nameLabel);
    layout->addWidget(nameEdit);

    QLabel *passwordLabel = new QLabel("密码:");
    passwordEdit = new QLineEdit();
    passwordEdit->setEchoMode(QLineEdit::Password);
    layout->addWidget(passwordLabel);
    layout->addWidget(passwordEdit);

    QHBoxLayout *buttonLayout = new QHBoxLayout();
    loginButton = new QPushButton("登录");
    registerButton = new QPushButton("注册");
    buttonLayout->addWidget(loginButton);
    buttonLayout->addWidget(registerButton);
    layout->addLayout(buttonLayout);

    connect(loginButton, &QPushButton::clicked, this, &LoginDialog::onLoginClicked);
    connect(registerButton, &QPushButton::clicked, this, &LoginDialog::onRegisterClicked);
}

void LoginDialog::onLoginClicked()
{

    QString name = nameEdit->text();
    QString password = passwordEdit->text();

    if (nameEdit->text().isEmpty() || passwordEdit->text().isEmpty()) {
        QMessageBox::warning(this, "错误", "用户名和密码不能为空");
        return;
    }

    if (db.verifyUser(name, password)) {
        accept();
    } else {
        QMessageBox::warning(this, "错误", "密码或者用户名错误");
    }
}


void LoginDialog::onRegisterClicked()
{
    QString name = nameEdit->text();
    QString password = passwordEdit->text();

    if (name.isEmpty() || password.isEmpty()) {
        QMessageBox::warning(this, "错误", "用户名和密码不能为空");
        return;
    }


    if (db.insertUser(name, password)) {
        QMessageBox::information(this, "成功", "注册成功");
    } else {
        QMessageBox::warning(this, "错误", "注册失败，用户名可能已存在");
    }
}
