#ifndef MANAGEUSER_H
#define MANAGEUSER_H

#include <QDialog>
#include <QStandardItemModel>
#include "src/User/User.h"
#include "utils/ListPackage/Listt/Listt.h"

namespace Ui {
class ManageUser;
}

class ManageUser : public QDialog
{
    Q_OBJECT

public:
    explicit ManageUser(QWidget *parent = 0);
    ~ManageUser();

private slots:
    void on_btnSearch_clicked();

    void on_tableUser_doubleClicked(const QModelIndex &index);

    void on_inputSearch_returnPressed();

    void on_comboRole_currentIndexChanged(int index);

    void on_btnReset_clicked();

    void on_btnDelete_clicked();

private:
    Ui::ManageUser *ui;
    QStandardItemModel *userModel;
    Listt<User>* userList;
    void clearInput();
};

#endif // MANAGEUSER_H
