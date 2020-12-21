#include "manageuser.h"
#include "ui_manageuser.h"
#include "src/User/UserService.h"
#include <QMessageBox>
#include <QAbstractItemView>
#include <QStringList>
#include "src/Role/RoleService.h"
#include "managerole.h"


ManageUser::ManageUser(QWidget *parent, User *sessionUser) :
    QDialog(parent),
    ui(new Ui::ManageUser)
{
    ui->setupUi(this);
    this->userModel = new QStandardItemModel();
    this->ui->tableUser->setModel(this->userModel);
    this->ui->tableUser->setEditTriggers(QAbstractItemView::NoEditTriggers);
    this->ui->btnAdd->setAutoDefault(false);
    this->ui->btnUpdate->setAutoDefault(false);
    this->ui->btnDelete->setAutoDefault(false);
    this->ui->btnReset->setAutoDefault(false);
    this->sessionUser = sessionUser;
    this->loadRole();
    this->msgBox = new QMessageBox(0);

}

ManageUser::~ManageUser()
{
    delete ui;
}

void ManageUser::on_btnSearch_clicked()
{
    try {

        UserService* userService = UserService::initUserService();
        this->userModel->clear();
        this->clearInput();

        QStringList horizontalHeader;
        horizontalHeader.append("Id");
        horizontalHeader.append(QString::fromUtf8("Họ và tên"));
        horizontalHeader.append(QString::fromUtf8("Giới tính"));
        horizontalHeader.append(QString::fromUtf8("Email"));
        horizontalHeader.append(QString::fromUtf8("SĐT"));
        horizontalHeader.append(QString::fromUtf8("Ngày sinh"));
        horizontalHeader.append(QString::fromUtf8("Quyền"));
        this->userModel->setHorizontalHeaderLabels(horizontalHeader);
        this->ui->tableUser->setColumnWidth(0, this->ui->tableUser->width()/10);

        if (this->ui->inputSearch->text() == QString("")){
            this->userList = userService->findAll();
        } else if (this->ui->radioFullanme->isChecked()){
            this->userList = userService->findByFullname(this->ui->inputSearch->text());
        } else if (this->ui->radioPhone->isChecked()){
            this->userList = userService->findByPhone(this->ui->inputSearch->text());
        } else if (this->ui->radioID->isChecked()){
            bool ok;
            int ID = this->ui->inputSearch->text().toInt(&ok);
            if (!ok){
                this->showMessageBox(QString::fromUtf8("Thông báo"), QString::fromUtf8("ID không hợp lệ"), QString::fromUtf8("Vui lòng kiểm tra lại thông tin"));
                return;
            } else {
                this->userList = userService->findById(ID);
            }
        } else {
            this->ui->radioFullanme->setChecked(true);
            this->userList = userService->findByFullname(this->ui->inputSearch->text());
        }

        for (int i = 0; i < userList->getSize(); i++) {
            User user = this->userList->get(i);
            QStandardItem *idCol = new QStandardItem(QString::number(user.getUserId()));
            QStandardItem *nameCol = new QStandardItem(user.getFullname());
            QString _gender = user.getGender() == 0 ? "Nam" : (user.getGender() == 1 ? QString::fromUtf8("Nữ") : QString::fromUtf8("Không xác định"));
            QStandardItem *gender = new QStandardItem(_gender);
            QStandardItem *email = new QStandardItem(user.getEmail());
            QStandardItem *phone = new QStandardItem(user.getPhone());
            QStandardItem *birthday = new QStandardItem(user.getBirthday().toString("dd/MM/yyyy"));
            QStandardItem *role = new QStandardItem(user.getRole().getDescription());
            this->userModel->appendRow( QList<QStandardItem*>() << idCol << nameCol << gender << email << phone << birthday << role);
        }
    } catch(const char* msg) {
        // show dialog instead console log
        qDebug() << msg;
    }

}

void ManageUser::on_tableUser_doubleClicked(const QModelIndex &index)
{
    this->ui->tableUser->selectRow(index.row());
    User user = this->userList->get(index.row());
    this->ui->inputFullname->setText(user.getFullname());
    this->ui->inputBirthday->setDate(user.getBirthday());
    this->ui->inputEmail->setText(user.getEmail());
    this->ui->inputAddress->setText(user.getAddress());
    this->ui->inputID->setText(QString::number(user.getUserId()));
    this->ui->inputPhone->setText(user.getPhone());
    this->ui->inputUsername->setText(user.getUsername());
    this->ui->comboGender->setCurrentIndex(user.getGender());
    this->ui->comboRole->setCurrentIndex(this->roleId2Index[user.getRole().getRoleId()]);
}

void ManageUser::clearInput(){
    this->ui->inputFullname->clear();
    this->ui->inputBirthday->clear();
    this->ui->inputEmail->clear();
    this->ui->inputAddress->clear();
    this->ui->inputID->clear();
    this->ui->inputPassword->clear();
    this->ui->inputPhone->clear();
    this->ui->inputUsername->clear();
    this->ui->comboGender->setCurrentIndex(0);
    this->ui->comboRole->setCurrentIndex(0);
}

void ManageUser::on_inputSearch_returnPressed()
{
    this->on_btnSearch_clicked();
}

void ManageUser::on_comboRole_currentIndexChanged(int index)
{
    if (index == 3){
        this->ui->inputUsername->setEnabled(false);
        this->ui->inputPassword->setEnabled(false);
    } else {
        this->ui->inputUsername->setEnabled(true);
        this->ui->inputPassword->setEnabled(true);
    }
}

void ManageUser::on_btnReset_clicked()
{
    this->clearInput();
}

void ManageUser::on_btnDelete_clicked()
{
    if (this->ui->tableUser->selectionModel()->selectedRows().size() == 0){
        this->showMessageBox(QString::fromUtf8("Thông báo"), QString::fromUtf8("Chưa chọn tài khoản"), QString::fromUtf8("Vui lòng lựa chọn tài khoản cần xóa"));
        return;
    }

    QString litsDelete = QString::fromUtf8("Bạn có chắc muốn xóa những tài khoản này?\n");
    Listt<User> *listUser = new LinkedListt<User>();
    for (int i = 0; i < this->ui->tableUser->selectionModel()->selectedRows().size();i++){
        int index = this->ui->tableUser->selectionModel()->selectedRows()[i].row();
        litsDelete += this->userList->get(index).getFullname() + "\n";
        listUser->add(this->userList->get(index));
    }
    //confirm
    QMessageBox::StandardButton reply;
    reply = QMessageBox::question(this, QString::fromUtf8("Xác nhận xóa"), litsDelete,
                                QMessageBox::Yes|QMessageBox::No);
    if (reply == QMessageBox::No) {
        delete listUser;
        return;
    }
    UserService* userService = UserService::initUserService();
    int result = userService->deleteUsers(listUser);
    if (result == -1){
        this->userList->clear();
        this->userModel->clear();
        return;
    }

    this->showMessageBox(QString::fromUtf8("Thông báo"), QString::fromUtf8("Đã xảy ra lỗi. Hãy chắc chắc tài khoản này đã trả đủ sách"), QString::fromUtf8("Đã xảy ra lỗi khi xóa tài khoản ") + listUser->get(result).getFullname());
    return;


}

User ManageUser::loadInfo(){
    int user_id = this->ui->inputID->text() == "" ? -1 : this->ui->inputID->text().toInt();
    QString fullname = this->ui->inputFullname->text();
    QDate birthday = this->ui->inputBirthday->date();
    int gender = this->ui->comboGender->currentIndex();
    QString phone = this->ui->inputPhone->text();
    QString email = this->ui->inputEmail->text();
    int role_index = this->ui->comboRole->currentIndex();
    QString username = this->ui->inputUsername->text();
    QString password = this->ui->inputPassword->text();
    QString address = this->ui->inputAddress->toPlainText();


    User user(user_id, fullname, birthday, gender, email, phone, username, password, this->listRole->get(role_index), address);
    // if guest -> set username and password to default
    if (user.getRole().getCode() == "guest"){
        user.setUsername(user.getPhone());
        user.setPassword("defaultPassword");
    } else {
    // if update -> check if update password
        if (user.getUserId() != -1 && password == ""){
            user.setPassword("defaultPassword");
        }
    }
    return user;
}

void ManageUser::on_btnAdd_clicked()
{
    User newUser = this->loadInfo();

    if (newUser.getRole().getPriorty() <= this->sessionUser->getRole().getPriorty()){
        this->showMessageBox(QString::fromUtf8("Thông báo"), QString::fromUtf8("Truy cập bị từ chối"), QString::fromUtf8("Bạn không có quyền thêm tài khoản cấp cao hơn"));
        return;
    }


    UserService* userService = UserService::initUserService();
    try{
        userService->addUser(newUser);
    } catch (QString &error){
        this->showMessageBox(QString::fromUtf8("Thông báo"), QString::fromUtf8("Không thể tạo tài khoản"), error);
        return;
    } catch (...){
        this->showMessageBox(QString::fromUtf8("Thông báo"), QString::fromUtf8("Không thể tạo tài khoản"), QString::fromUtf8("Vui lòng kiểm tra lại thông tin"));
        return;
    }

    this->clearInput();
    this->ui->inputSearch->setText(newUser.getFullname());
    this->ui->radioFullanme->setChecked(true);
    this->on_btnSearch_clicked();

}

void ManageUser::on_btnUpdate_clicked()
{
    if (this->ui->inputID->text() == ""){
        this->showMessageBox(QString::fromUtf8("Thông báo"), QString::fromUtf8("Bạn chưa chọn tài khoản cần cập nhật"), QString::fromUtf8("Vui lòng chọn tài khoản cần cập nhật"));
        return;
    }

    User user = this->loadInfo();

    if (user.getRole().getPriorty() <= this->sessionUser->getRole().getPriorty()){
        this->showMessageBox(QString::fromUtf8("Thông báo"), QString::fromUtf8("Truy cập bị từ chối"), QString::fromUtf8("Bạn không có quyền cập nhật tài khoản này"));
        return;
    }

    UserService* userService = UserService::initUserService();
    try{
        userService->updateUser(user);
    } catch (QString &error){
        this->showMessageBox(QString::fromUtf8("Thông báo"), QString::fromUtf8("Đã xảy ra lỗi"), error);
        return;
    } catch (...){
        this->showMessageBox(QString::fromUtf8("Thông báo"), QString::fromUtf8("Đã xảy ra lỗi"), QString::fromUtf8("Lỗi không xác định"));
        return;
    }

    this->clearInput();
    this->ui->inputSearch->setText(user.getFullname());
    this->ui->radioFullanme->setChecked(true);
    this->on_btnSearch_clicked();

}

void ManageUser::loadRole(){
    RoleService* roleService = RoleService::initRoleService();
    this->listRole = roleService->findAll();
    this->ui->comboRole->clear();
    this->roleId2Index.clear();
    QStringList listText;
    for (int i = 0;i < listRole->getSize();i++){
        Role role = this->listRole->get(i);
        listText.append(role.getDescription());
        this->roleId2Index[role.getRoleId()] = i;
    }
    this->ui->comboRole->addItems(listText);
}

int ManageUser::showMessageBox(QString title, QString text, QString info){
    this->msgBox->setWindowTitle(title);
    this->msgBox->setText(text);
    this->msgBox->setInformativeText(info);
    return this->msgBox->exec();

}

