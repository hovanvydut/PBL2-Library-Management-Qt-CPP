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
    this->userModel = new QStandardItemModel();
    this->bookModel = new QStandardItemModel();
    this->selectedBookModel = new QStandardItemModel();
    this->ui->tableUsers->setModel(this->userModel);
    this->ui->tableBooks->setModel(this->bookModel);
    this->ui->tableSeletedBooks->setModel(this->selectedBookModel);
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
        this->userModel->clear();

        QStringList horizontalHeader;
        horizontalHeader.append("Id");
        horizontalHeader.append(QString::fromUtf8("Họ và tên"));
        horizontalHeader.append(QString::fromUtf8("Giới tính"));
        horizontalHeader.append(QString::fromUtf8("Email"));
        horizontalHeader.append(QString::fromUtf8("SĐT"));
        horizontalHeader.append(QString::fromUtf8("Ngày sinh"));
        this->userModel->setHorizontalHeaderLabels(horizontalHeader);
        this->ui->tableUsers->setColumnWidth(0, this->ui->tableBooks->width()/10);

        Listt<User>* userList;
        if (this->ui->radioUserName->isChecked()){
             userList = userService->findByFullname(this->ui->inputUserSearch->text());
        } else if (this->ui->radioUserPhone->isChecked()){
            userList = userService->findByPhone(this->ui->inputUserSearch->text());
        } else if (this->ui->radioUserId->isChecked()){
            bool ok;
            int ID = this->ui->inputUserSearch->text().toInt(&ok);
            if (!ok){
                QMessageBox *msgBox = new QMessageBox(0);
                msgBox->setWindowTitle(QString::fromUtf8("Thông báo"));
                msgBox->setText(QString::fromUtf8("ID không hợp lệ"));
                msgBox->setInformativeText(QString::fromUtf8("Vui lòng kiểm tra lại thông tin"));
                msgBox->exec();
                return;
            } else {
                userList = userService->findById(ID);
            }
        } else {
            this->ui->radioUserName->setChecked(true);
            userList = userService->findByFullname(this->ui->inputUserSearch->text());
        }
        for (int i = 0; i < userList->getSize(); i++) {
            User user = userList->get(i);
            QStandardItem *idCol = new QStandardItem(QString::number(user.getUserId()));
            QStandardItem *nameCol = new QStandardItem(user.getFullname());
            QString _gender = user.getGender() == 0 ? "Nam" : (user.getGender() == 1 ? QString::fromUtf8("Nữ") : QString::fromUtf8("Không xác định"));
            QStandardItem *gender = new QStandardItem(_gender);
            QStandardItem *email = new QStandardItem(user.getEmail());
            QStandardItem *phone = new QStandardItem(user.getPhone());
            this->userModel->appendRow( QList<QStandardItem*>() << idCol << nameCol << gender << email << phone);
        }
    } catch(const char* msg) {
        // show dialog instead console log
        qDebug() << msg;
    }

}

void MainWindow::on_tableUsers_doubleClicked(const QModelIndex &index)
{
    this->ui->tableUsers->selectRow(index.row());
    int id = this->ui->tableUsers->model()->itemData(index.sibling(index.row(), 0)).value(0).toInt();
    QString fullname = this->ui->tableUsers->model()->itemData(index.sibling(index.row(), 1)).value(0).toString();
    QString gender = this->ui->tableUsers->model()->itemData(index.sibling(index.row(), 2)).value(0).toString();
    QString email = this->ui->tableUsers->model()->itemData(index.sibling(index.row(), 3)).value(0).toString();
    QString phone = this->ui->tableUsers->model()->itemData(index.sibling(index.row(), 4)).value(0).toString();
    QString info = QString::fromUtf8("Họ và tên: ") + fullname
            + QString::fromUtf8("\nGiới tính: ") + gender
            + QString::fromUtf8("\nĐiện thoại: ") + phone
            + QString::fromUtf8("\nEmal: ") + email;
    //delete this->selectedUser;
    this->selectedUser = new User(id, fullname);
    this->ui->textUserInfo->setText(info);
}

void MainWindow::on_btnAllBorrowBook_clicked()
{
    UserService* userService = UserService::initUserService();
    if (this->selectedUser == NULL){
        QMessageBox *msgBox = new QMessageBox(0);
        msgBox->setWindowTitle(QString::fromUtf8("Thông báo"));
        msgBox->setText(QString::fromUtf8("Chưa lựa chọn tài khoản"));
        msgBox->setInformativeText(QString::fromUtf8("Vui lòng tìm kiếm và chọn tài khoản"));
        msgBox->exec();
        return;
    }
    Listt<BorrowBook>* borrowList = userService->getBorrowBook(this->selectedUser->getUserId());

    if (borrowList->getSize() == 0){
        QMessageBox *msgBox = new QMessageBox(0);
        msgBox->setWindowTitle(QString::fromUtf8("Thông báo"));
        msgBox->setText(QString::fromUtf8("Người này chưa từng mượn sách"));
        msgBox->setInformativeText(QString::fromUtf8("Tài khoản này chưa từng mượn sách"));
        msgBox->exec();
        delete borrowList;
        return;
    } else {
        this->selectedUser->borrowList = borrowList;
    }

    QStringList horizontalHeader;
    horizontalHeader.append("Id");
    horizontalHeader.append(QString::fromUtf8("Tên sách"));
    horizontalHeader.append(QString::fromUtf8("Số sách mượn"));
    horizontalHeader.append(QString::fromUtf8("Ngày mượn"));
    horizontalHeader.append(QString::fromUtf8("Số ngày mượn"));
    horizontalHeader.append(QString::fromUtf8("Hết hạn"));
    horizontalHeader.append(QString::fromUtf8("Tiền cọc"));
    this->bookModel->clear();
    this->bookModel->setHorizontalHeaderLabels(horizontalHeader);
    this->selectedBookModel->clear();
    this->selectedBookModel->setHorizontalHeaderLabels(horizontalHeader);


    for (int i = 0;i < this->selectedUser->borrowList->getSize();i++){
        BorrowBook borrow = this->selectedUser->borrowList->get(i);

        QStandardItem *idCol = new QStandardItem(QString::number(borrow.getId()));
        QStandardItem *title = new QStandardItem(borrow.getBook().getTitle());
        QStandardItem *quantity = new QStandardItem(QString::number(borrow.getQuantity()));
        QStandardItem *dateBorrow = new QStandardItem(borrow.getBorrowedAt().toString("dd/MM/yyyy"));
        QStandardItem *numOfDay = new QStandardItem(QString::number(borrow.getNumOfDay()));
        QStandardItem *deadline = new QStandardItem(borrow.getBorrowedAt().addDays(borrow.getNumOfDay()).toString("dd/MM/yyyy"));
        QStandardItem *depositMoney = new QStandardItem(QString::number(borrow.getDepositMoney()));
        this->bookModel->appendRow( QList<QStandardItem*>() << idCol << title << quantity << dateBorrow << numOfDay << deadline << depositMoney);
    }
    this->ui->tableBooks->setColumnWidth(0, this->ui->tableBooks->width()/10);
    this->ui->tableBooks->setEditTriggers(QAbstractItemView::NoEditTriggers);
}

void MainWindow::on_tableBooks_doubleClicked(const QModelIndex &index)
{
    this->ui->tableBooks->selectRow(index.row());
    QList<QStandardItem*> row;
    for (int i = 0;i < this->bookModel->columnCount();i++){
        row << this->bookModel->item(index.row(), i)->clone();
    }
    this->selectedBookModel->appendRow(row);
    this->bookModel->removeRow(index.row());
    //this->selectedBookModel->appendRow(QList<QStandardItem*>() << this->bookModel->item(index.row(), 1) << this->bookModel->item(index.row(), 2));
}

void MainWindow::on_tableSeletedBooks_doubleClicked(const QModelIndex &index)
{
    this->ui->tableSeletedBooks->selectRow(index.row());
    QList<QStandardItem*> row;
    for (int i = 0;i < this->selectedBookModel->columnCount();i++){
        row << this->selectedBookModel->item(index.row(), i)->clone();
    }
    this->bookModel->appendRow(row);
    this->selectedBookModel->removeRow(index.row());
}
