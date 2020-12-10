#ifndef LOGINDIALOG_H
#define LOGINDIALOG_H

#include <QDialog>
#include <mainwindow.h>
#include <QString>
#include <QMessageBox>

namespace Ui {
class LoginDialog;
}

class LoginDialog : public QDialog
{
    Q_OBJECT

public:
    explicit LoginDialog(QWidget *parent = NULL);
    QString getUserID();
    ~LoginDialog();

private slots:
    void on_btnLogin_clicked();

private:
    Ui::LoginDialog *ui;
    QString userID;

};

#endif // LOGINDIALOG_H
