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

User LoginDialog::getUser(){
    return this->user;
}

void LoginDialog::on_btnLogin_clicked()
{
    UserService *userService = UserService::initUserService();
    Listt<User> *result = userService->findByUsername(this->ui->username->text());
    if (result->getSize() != 0){
        Password pwd(this->ui->password->text());
        if (pwd.compare(result->get(0).getPassword()) && result->get(0).getRole().getCode() != "guest"){
            this->user = result->get(0);
            this->accept();
            return;
        }
    }

    QMessageBox *msgBox = new QMessageBox(0);
    msgBox->setWindowTitle(QString::fromUtf8("Lỗi thông tin"));
    msgBox->setText(QString::fromUtf8("Sai thông tin đăng nhập"));
    msgBox->setInformativeText(QString::fromUtf8("Vui lòng kiểm tra thông tin đăng nhập"));
    msgBox->exec();

}
