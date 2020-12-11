#include "mainwindow.h"
#include "ui_mainwindow.h"
#include "src/Publisher/PublisherService.h"
#include "utils/ListPackage/Listt/Listt.h"
#include <QStandardItem>
#include <QDebug>
#include "src/Category/CategoryService.h"
#include "src/IssuingCompany/IssuingCompanyService.h"
#include "src/Author/AuthorService.h"
#include <QDialog>
#include "src/Book/BookService.h"
#include "src/User/User.h"
#include "src/User/UserService.h"
#include <QString>

MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow)
{
    ui->setupUi(this);
}


void MainWindow::showAndLogin(){
    QMainWindow::show();
    this->login();
    //this->loginDialog = new LoginDialog(this);
    //this->loginDialog->show();
}

void MainWindow::login(){
    LoginDialog *login = new LoginDialog();
    login->show();
    this->hide();
    if (login->exec() == QDialog::Accepted) {
       qDebug() << login->getUserID();
       delete login;
       this->show();
    }
}

MainWindow::~MainWindow()
{
    delete ui;
}

void MainWindow::on_btnSearchBook_clicked()
{
    BookService* bookService = BookService::initBookService();

    AuthorService* authorService = AuthorService::initAuthorService();

    // Tìm kiếm theo mã sách
    if (ui->radioBookId->isChecked())
    {
        QString text = ui->inputBookSearch->text();
        int theId = text.toInt();
        qDebug() << "id --> " << theId;

        // Trường hợp mã Id người dùng nhập vào không hợp lệ --> convert lỗi --> default = 0
        if (theId == 0)
        {
            POPUP_MSG:
            QMessageBox *msgBox = new QMessageBox(0);
            msgBox->setWindowTitle(QString::fromUtf8("Thông báo"));
            msgBox->setText(QString::fromUtf8("Không tìm thấy kết quả"));
            msgBox->setInformativeText(QString::fromUtf8("Vui lòng kiểm tra lại thông tin"));
            msgBox->exec();
        }
        else
        {
            Book book = bookService->findById(theId);

            // Không tìm thấy sách
            if (book.getId() == 0)
                goto POPUP_MSG;

            QStandardItemModel *model = new QStandardItemModel();
            QStringList horizontalHeader;
            horizontalHeader.append("Id");
            horizontalHeader.append(QString::fromUtf8("Tên sách"));
            horizontalHeader.append(QString::fromUtf8("Tổng số"));
            horizontalHeader.append(QString::fromUtf8("Hiện có"));
            model->setHorizontalHeaderLabels(horizontalHeader);
            ui->tableBooks->setModel(model);

            QStandardItem *idCol = new QStandardItem(QString::number(book.getId()));
            QStandardItem *nameCol = new QStandardItem(book.getTitle());
            QStandardItem *total = new QStandardItem(QString::number(book.getTotal()));
            QStandardItem *available = new QStandardItem(QString::number(book.getAvailable()));
            model->appendRow( QList<QStandardItem*>() << idCol << nameCol << total << available);
        }
    }
    // Tìm kiếm theo tên sách
    else if (ui->radioBookName->isChecked())
    {
        QString title = ui->inputBookSearch->text();

        Listt<Book>* bookList = bookService->findByBookTitle(title);

        QStandardItemModel *model = new QStandardItemModel();
        QStringList horizontalHeader;
        horizontalHeader.append("Id");
        horizontalHeader.append(QString::fromUtf8("Tên sách"));
        horizontalHeader.append(QString::fromUtf8("Tổng số"));
        horizontalHeader.append(QString::fromUtf8("Hiện có"));
        model->setHorizontalHeaderLabels(horizontalHeader);
        ui->tableBooks->setModel(model);

        for (int i = 0; i < bookList->getSize(); i++) {
            Book book = bookList->get(i);
            QStandardItem *idCol = new QStandardItem(QString::number(book.getId()));
            QStandardItem *nameCol = new QStandardItem(book.getTitle());
            QStandardItem *total = new QStandardItem(QString::number(book.getTotal()));
            QStandardItem *available = new QStandardItem(QString::number(book.getAvailable()));
            model->appendRow( QList<QStandardItem*>() << idCol << nameCol << total << available);
        }
    }
    // Tìm kiếm theo tên tác giả
    else if (ui->radioBookAuthor->isChecked())
    {
        QString authorName = ui->inputBookSearch->text();

        Listt<Author>* listAuthor = authorService->findBooksOfAuthorByAuthorName(authorName);

        QStandardItemModel *model = new QStandardItemModel();
        QStringList horizontalHeader;
        horizontalHeader.append("Id");
        horizontalHeader.append(QString::fromUtf8("Tên sách"));
        horizontalHeader.append(QString::fromUtf8("Tổng số"));
        horizontalHeader.append(QString::fromUtf8("Hiện có"));
        horizontalHeader.append(QString::fromUtf8("Tác giả"));
        model->setHorizontalHeaderLabels(horizontalHeader);
        ui->tableBooks->setModel(model);

        for (int i = 0; i < listAuthor->getSize(); i++) {
            Author author = listAuthor->get(i);
            Listt<Book>* listBook = author.getBooks();

            for (int j = 0; j <listBook->getSize(); j++)
            {
                Book book = listBook->get(j);
                QStandardItem *idCol = new QStandardItem(QString::number(book.getId()));
                QStandardItem *nameCol = new QStandardItem(book.getTitle());
                QStandardItem *total = new QStandardItem(QString::number(book.getTotal()));
                QStandardItem *available = new QStandardItem(QString::number(book.getAvailable()));
                QStandardItem *authorName = new QStandardItem(author.getName());
                model->appendRow( QList<QStandardItem*>() << idCol << nameCol << total << available << authorName);
            }
        }
    }
    else
    {
        try {

            Listt<Book>* bookList = bookService->findAll();
            QStandardItemModel *model = new QStandardItemModel();
            QStringList horizontalHeader;
            horizontalHeader.append("Id");
            horizontalHeader.append(QString::fromUtf8("Tên sách"));
            horizontalHeader.append(QString::fromUtf8("Tổng số"));
            horizontalHeader.append(QString::fromUtf8("Hiện có"));
            model->setHorizontalHeaderLabels(horizontalHeader);
//            ui->tableView->setModel(model);
            ui->tableBooks->setModel(model);

            for (int i = 0; i < bookList->getSize(); i++) {
                Book book = bookList->get(i);
                QStandardItem *idCol = new QStandardItem(QString::number(book.getId()));
                QStandardItem *nameCol = new QStandardItem(book.getTitle());
                QStandardItem *total = new QStandardItem(QString::number(book.getTotal()));
                QStandardItem *available = new QStandardItem(QString::number(book.getAvailable()));
                model->appendRow( QList<QStandardItem*>() << idCol << nameCol << total << available);
            }
        } catch(const char* msg) {
            // show dialog instead console log
            qDebug() << msg;
        }
    }
}

void MainWindow::on_inputUserSearch_returnPressed()
{
    try {
        UserService* userService = UserService::initUserService();
        Listt<User>* userList = userService->findAll();

        QStandardItemModel *model = new QStandardItemModel();
        QStringList horizontalHeader;
        horizontalHeader.append("Id");
        horizontalHeader.append(QString::fromUtf8("Họ và tên"));
        horizontalHeader.append(QString::fromUtf8("Giới tính"));
        horizontalHeader.append(QString::fromUtf8("Email"));
        horizontalHeader.append(QString::fromUtf8("SĐT"));
        horizontalHeader.append(QString::fromUtf8("Ngày sinh"));
        model->setHorizontalHeaderLabels(horizontalHeader);
//            ui->tableView->setModel(model);
        ui->tableUsers->setModel(model);

        for (int i = 0; i < userList->getSize(); i++) {
            User user = userList->get(i);
            QStandardItem *idCol = new QStandardItem(QString::number(user.getUserId()));
            QStandardItem *nameCol = new QStandardItem(user.getFullname());
            QString _gender = user.getGender() == 0 ? "Nam" : (user.getGender() == 1 ? QString::fromUtf8("Nữ") : QString::fromUtf8("Không xác định"));
            QStandardItem *gender = new QStandardItem(_gender);
            QStandardItem *email = new QStandardItem(user.getEmail());
            QStandardItem *phone = new QStandardItem(user.getPhone());
            model->appendRow( QList<QStandardItem*>() << idCol << nameCol << gender << email << phone);
        }
    } catch(const char* msg) {
        // show dialog instead console log
        qDebug() << msg;
    }

}

void MainWindow::on_tableUsers_doubleClicked(const QModelIndex &index)
{
    qDebug() << this->ui->tableUsers->model()->index(0, 0);
}
