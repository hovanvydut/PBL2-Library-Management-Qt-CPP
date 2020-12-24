#ifndef MANAGEUSER_H
#define MANAGEUSER_H

#include <QDialog>
#include <QStandardItemModel>
#include "src/User/User.h"
#include "utils/ListPackage/Listt/Listt.h"
#include <QMap>
#include <QMessageBox>

namespace Ui {
class ManageUser;
}

class ManageUser : public QDialog
{
    Q_OBJECT

public:
    explicit ManageUser(QWidget *parent = 0, User *sessionUser = 0);
    ~ManageUser();

private slots:
    void on_btnSearch_clicked();

    void on_tableUser_doubleClicked(const QModelIndex &index);

    void on_inputSearch_returnPressed();

    void on_comboRole_currentIndexChanged(int index);

    void on_btnReset_clicked();

    void on_btnDelete_clicked();

    void on_btnAdd_clicked();

    void on_btnUpdate_clicked();

    void on_btnSort_clicked();

private:
    Ui::ManageUser *ui;
    QStandardItemModel *userModel;
    Listt<User>* userList;
    void clearInput();
    User loadInfo();
    void loadRole();
    User *sessionUser;
    Listt<Role> *listRole;
    QMap<int, int> roleId2Index;
    QMessageBox *msgBox;
    void listToModel();
    int showMessageBox(QString = "", QString = "", QString = "");

};

#endif // MANAGEUSER_H
