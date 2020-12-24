#ifndef MANAGEROLE_H
#define MANAGEROLE_H

#include <QDialog>
#include "src/Role/RoleService.h"
#include "utils/ListPackage/Listt/Listt.h"
#include <QMessageBox>

namespace Ui {
class ManageRole;
}

class ManageRole : public QDialog
{
    Q_OBJECT

public:
    explicit ManageRole(QWidget *parent = 0);
    ~ManageRole();

private slots:
    void on_btnDelete_clicked();

    void on_btnAdd_clicked();

private:
    Ui::ManageRole *ui;
    void loadRole();
    Listt<Role> *listRole;
    Role loadRoleFromInput();
    void clearInput();
    QMessageBox *msgBox;
    int showMessageBox(QString = "", QString = "", QString = "");

};

#endif // MANAGEROLE_H
