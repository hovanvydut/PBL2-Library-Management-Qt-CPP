#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <logindialog.h>
#include <QModelIndex>
#include <QStandardItemModel>
#include "src/User/User.h"
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

private:
    Ui::MainWindow *ui;
    void login();
    User *selectedUser;
    QStandardItemModel *userModel;
    QStandardItemModel *bookModel;
    QStandardItemModel *selectedBookModel;
    int mode; // = 0 if borrow else = 1 if return book
};

#endif // MAINWINDOW_H
