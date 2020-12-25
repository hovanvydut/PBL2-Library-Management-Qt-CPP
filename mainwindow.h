#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <QMap>
#include <logindialog.h>
#include <QModelIndex>
#include <QStandardItemModel>
#include "src/User/User.h"
#include "ui_component/manage_publisher/ManagePublisher.h"
#include "ui_component/manage_category/ManageCategory.h"
#include "ui_component/manage_issuing_company/ManageIssuingCompany.h"
#include "ui_component/manage_author/Manage_Author.h"

#include <QMessageBox>
namespace Ui {
class MainWindow;
}

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    explicit MainWindow(QWidget *parent = 0);
    void showAndLogin();
    ~MainWindow();

//private slots:
//    void on_pushButton_clicked();

//    void on_pushButton_2_clicked();

//    void on_pushButton_3_clicked();

//    void on_pushButton_4_clicked();

private slots:
    void on_btnSearchBook_clicked();

    void on_inputUserSearch_returnPressed();

    void on_tableUsers_doubleClicked(const QModelIndex &index);

    void on_btnAllBorrowBook_clicked();

    void on_tableBooks_doubleClicked(const QModelIndex &index);

    void on_tableSeletedBooks_doubleClicked(const QModelIndex &index);

    void on_btnReturnBook_clicked();

    void on_menuAdminShowUsers_triggered();

    void on_menuAdminShowBook_triggered();
    void on_menuLogout_triggered();

    void on_menuUserInfo_triggered();

    void on_actionTh_ng_tin_quy_n_triggered();

    void on_menu_publisher_triggered();

    void on_menu_category_triggered();

    void on_menu_issuing_company_triggered();

    void on_btnBorrowBook_clicked();

    void on_actionT_c_gi_triggered();

    void on_tableSeletedBooks_pressed(const QModelIndex &index);

private:
    Ui::MainWindow *ui;
    void login();
    Listt<BorrowBook>* getDataBorrow();
    User *sessionUser;
    User *selectedUser;
    QStandardItemModel *userModel;
    QStandardItemModel *bookModel;
    QStandardItemModel *selectedBookModel;
    int mode; // = 0 if borrow else = 1 if return book
    QMessageBox *msgBox;
    int showMessageBox(QString = "", QString = "", QString = "");
    void clearData();
};

#endif // MAINWINDOW_H
