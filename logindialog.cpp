#include "logindialog.h"
#include "ui_logindialog.h"

LoginDialog::LoginDialog(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::LoginDialog)
{
    ui->setupUi(this);
}

LoginDialog::~LoginDialog()
{
    delete ui;
}

QString LoginDialog::getUserID(){
    return this->userID;
}

void LoginDialog::on_btnLogin_clicked()
{
    if (this->ui->username->text() == "admin" && this->ui->password->text() == "admin"){
        this->userID = "admin";
        this->accept();
    } else {
        QMessageBox *msgBox = new QMessageBox(0);
        msgBox->setWindowTitle(QString::fromUtf8("Lỗi thông tin"));
        msgBox->setText(QString::fromUtf8("Sai thông tin đăng nhập"));
        msgBox->setInformativeText(QString::fromUtf8("Vui lòng kiểm tra thông tin đăng nhập"));
        msgBox->exec();
    }

}
