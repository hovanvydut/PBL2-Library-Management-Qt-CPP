#ifndef LOGINDIALOG_H
#define LOGINDIALOG_H

#include <QDialog>
#include <mainwindow.h>
#include <QString>
#include <QMessageBox>
#include "src/User/UserService.h"
#include "utils/Auth/Password.h"

namespace Ui {
class LoginDialog;
}

class LoginDialog : public QDialog
{
    Q_OBJECT

public:
    explicit LoginDialog(QWidget *parent = NULL);
    User getUser();
    ~LoginDialog();

private slots:
    void on_btnLogin_clicked();

private:
    Ui::LoginDialog *ui;
    User user;

};

#endif // LOGINDIALOG_H
