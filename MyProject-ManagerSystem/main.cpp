#include "mainwindow.h"
#include "logindialog.h"
#include <qsettings.h>
#include<QFile>

#include <QApplication>

int main(int argc, char *argv[])
{

    QApplication a(argc, argv);

    LoginDialog loginDialog;
    if (loginDialog.exec() == QDialog::Accepted) {
        MainWindow w;
        w.show();
        return a.exec();
    }

    return 0;
}
