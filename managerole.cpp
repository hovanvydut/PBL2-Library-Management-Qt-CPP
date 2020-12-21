#include "managerole.h"
#include "ui_managerole.h"
#include <QMessageBox>
#include <QString>
#include <QDebug>

ManageRole::ManageRole(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::ManageRole)
{
    ui->setupUi(this);
    this->loadRole();
    this->msgBox = new QMessageBox(0);
}

ManageRole::~ManageRole()
{
    delete ui;
}

void ManageRole::loadRole(){
    RoleService* roleService = RoleService::initRoleService();
    this->listRole = roleService->findAll();
    this->ui->comboBoxRole->clear();
    QStringList listText;
    for (int i = 0;i < listRole->getSize();i++){
        Role role = this->listRole->get(i);
        listText.append(role.getDescription());
    }
    this->ui->comboBoxRole->addItems(listText);
}

void ManageRole::on_btnDelete_clicked()
{
    RoleService* roleService = RoleService::initRoleService();
    Role role = this->listRole->get(this->ui->comboBoxRole->currentIndex());
    QMessageBox::StandardButton reply;
    reply = QMessageBox::question(this, QString::fromUtf8("Xác nhận xóa"),
                                  QString::fromUtf8("Những tài khoản thuộc quyền này củng sẽ bị xóa. Bạn có chắc muốn xóa quyền ") + role.getDescription(),
                                  QMessageBox::Yes|QMessageBox::No);
    if (reply == QMessageBox::No) {
        return;
    }

    try{
        roleService->deleteRole(role.getRoleId());
    } catch (QString &error){
        this->showMessageBox(QString::fromUtf8("Thông báo"), QString::fromUtf8("Lỗi trong lúc xóa"), error);
        return;
    } catch (...){
        this->showMessageBox(QString::fromUtf8("Thông báo"), QString::fromUtf8("Lỗi trong lúc xóa"), QString::fromUtf8("Lỗi không xác định"));
        return;
    }
    this->loadRole();
}

Role ManageRole::loadRoleFromInput(){
    bool ok;
    if (this->ui->inputCode->text() == "" || this->ui->inputDescription->text() == "" || this->ui->inputPriorty->text() == ""){
        throw QString::fromUtf8("Vui lòng điền đầy đủ các trường");
    }
    int priorty = this->ui->inputPriorty->text().toInt(&ok);
    if (!ok || priorty <= 0 || priorty >= 100){
        throw QString::fromUtf8("Độ ưu tiên phải là số nguyên dương từ 1 -> 100");
    }
    return Role(-1, priorty, this->ui->inputCode->text(), this->ui->inputDescription->text());
}

int ManageRole::showMessageBox(QString title, QString text, QString info){
    this->msgBox->setWindowTitle(title);
    this->msgBox->setText(text);
    this->msgBox->setInformativeText(info);
    return this->msgBox->exec();

}

void ManageRole::on_btnAdd_clicked()
{
    RoleService* roleService = RoleService::initRoleService();

    try {
        Role role = this->loadRoleFromInput();
        roleService->addNew(role);
    } catch (QString &error){
        this->showMessageBox(QString::fromUtf8("Thông báo"), QString::fromUtf8("Đã có lỗi xảy ra"), error);
        return;
    } catch (...){
        this->showMessageBox(QString::fromUtf8("Thông báo"), QString::fromUtf8("Đã có lỗi xảy ra"), QString::fromUtf8("Lỗi không xác định"));
        return;
    }
    this->clearInput();
    this->loadRole();
}

void ManageRole::clearInput(){
    this->ui->inputCode->clear();
    this->ui->inputDescription->clear();
    this->ui->inputPriorty->clear();
}
