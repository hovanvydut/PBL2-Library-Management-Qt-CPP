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
#include "manageuser.h"
#include "managebook.h"
#include "managerole.h"
#include <QStandardItem>
#include <QModelIndex>

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
    this->mode = 0;
    this->selectedUser = nullptr;
    this->msgBox = new QMessageBox(0);
}


void MainWindow::showAndLogin(){
    QMainWindow::show();
    this->login();
}

void MainWindow::login(){
    LoginDialog *login = new LoginDialog();
    login->show();
    this->hide();
    int result = login->exec();
    if (result == QDialog::Accepted) {
       this->sessionUser = new User(login->getUser());
       this->setWindowTitle(QString::fromUtf8("Quán lí thư viện - ") + this->sessionUser->getFullname());
       delete login;
       this->show();
    } else {
        delete login;
        this->close();
    }
}

MainWindow::~MainWindow()
{
    delete ui;
//    delete sessionUser;
//    delete selectedUser;
//    delete userModel;
//    delete bookModel;
//    delete selectedBookModel;
//    delete msgBox;
}

void MainWindow::on_btnSearchBook_clicked()
{
    if (this->mode == 1){
        this->mode = 0;
        this->selectedBookModel->clear();
        this->bookModel->clear();
    }

    BookService* bookService = BookService::initBookService();
    this->ui->tableSeletedBooks->setEditTriggers(QAbstractItemView::AllEditTriggers);
    AuthorService* authorService = AuthorService::initAuthorService();
    //set up table
    this->ui->tableSeletedBooks->setEditTriggers(QAbstractItemView::AllEditTriggers);

    //set up table
    QStringList horizontalHeader;
    horizontalHeader.append("Id");
    horizontalHeader.append(QString::fromUtf8("Tên sách"));
    horizontalHeader.append(QString::fromUtf8("Tổng số"));
    horizontalHeader.append(QString::fromUtf8("Hiện có"));
    this->bookModel->clear();
    this->bookModel->setHorizontalHeaderLabels(horizontalHeader);

    QStringList horizontalHeader2;
    horizontalHeader2.append("Id");
    horizontalHeader2.append(QString::fromUtf8("Tên sách"));
    horizontalHeader2.append(QString::fromUtf8("Hiện có"));
    horizontalHeader2.append(QString::fromUtf8("Số lượng mượn"));
    horizontalHeader2.append(QString::fromUtf8("Số ngày mượn"));
    horizontalHeader2.append(QString::fromUtf8("Tiền cọc"));
    //this->selectedBookModel->clear();
    this->selectedBookModel->setHorizontalHeaderLabels(horizontalHeader2);

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

            QStandardItem *idCol = new QStandardItem(QString::number(book.getId()));
            QStandardItem *nameCol = new QStandardItem(book.getTitle());
            QStandardItem *total = new QStandardItem(QString::number(book.getTotal()));
            QStandardItem *available = new QStandardItem(QString::number(book.getAvailable()));
            this->bookModel->appendRow( QList<QStandardItem*>() << idCol << nameCol << total << available);
        }
    }
    // Tìm kiếm theo tên sách
    else if (ui->radioBookName->isChecked())
    {
        QString title = ui->inputBookSearch->text();

        Listt<Book>* bookList = bookService->findByBookTitle(title);

        for (int i = 0; i < bookList->getSize(); i++) {
            Book book = bookList->get(i);
            QStandardItem *idCol = new QStandardItem(QString::number(book.getId()));
            QStandardItem *nameCol = new QStandardItem(book.getTitle());
            QStandardItem *total = new QStandardItem(QString::number(book.getTotal()));
            QStandardItem *available = new QStandardItem(QString::number(book.getAvailable()));
            this->bookModel->appendRow( QList<QStandardItem*>() << idCol << nameCol << total << available);
        }
    }
    // Tìm kiếm theo tên tác giả
    else if (ui->radioBookAuthor->isChecked())
    {
        QString authorName = ui->inputBookSearch->text();

        Listt<Author>* listAuthor = authorService->findBooksOfAuthorByAuthorName(authorName);

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
                this->bookModel->appendRow( QList<QStandardItem*>() << idCol << nameCol << total << available << authorName);
            }
        }
    }
    else
    {
        try {

            Listt<Book>* bookList = bookService->findAll();

            for (int i = 0; i < bookList->getSize(); i++) {
                Book book = bookList->get(i);
                QStandardItem *idCol = new QStandardItem(QString::number(book.getId()));
                QStandardItem *nameCol = new QStandardItem(book.getTitle());
                QStandardItem *total = new QStandardItem(QString::number(book.getTotal()));
                QStandardItem *available = new QStandardItem(QString::number(book.getAvailable()));
                this->bookModel->appendRow( QList<QStandardItem*>() << idCol << nameCol << total << available);
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
                this->showMessageBox(QString::fromUtf8("Thông báo"), QString::fromUtf8("ID không hợp lệ"), QString::fromUtf8("Vui lòng kiểm tra lại thông tin"));
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
            QStandardItem *birthday = new QStandardItem(user.getBirthday().toString("dd/MM/yyyy"));
            this->userModel->appendRow( QList<QStandardItem*>() << idCol << nameCol << gender << email << phone << birthday);
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
    if (this->mode == 0){
        this->mode = 1;
        this->selectedBookModel->clear();
        this->bookModel->clear();
    }
    UserService* userService = UserService::initUserService();
    if (this->selectedUser == NULL){
        this->showMessageBox(QString::fromUtf8("Thông báo"), QString::fromUtf8("Chưa lựa chọn tài khoản"), QString::fromUtf8("Vui lòng tìm kiếm và chọn tài khoản"));
        return;
    }
    Listt<BorrowBook>* borrowList = userService->getBorrowBook(this->selectedUser->getUserId());

    if (borrowList->getSize() == 0){
        this->showMessageBox(QString::fromUtf8("Thông báo"), QString::fromUtf8("Người này chưa từng mượn sách"), QString::fromUtf8("Tài khoản này chưa từng mượn sách"));
        delete borrowList;
        return;
    } else {
        this->selectedUser->borrowList = borrowList;
    }

    QStringList horizontalHeader;
    horizontalHeader.append("ID");
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
    this->ui->tableSeletedBooks->setEditTriggers(QAbstractItemView::NoEditTriggers);

}

void MainWindow::on_tableBooks_doubleClicked(const QModelIndex &index)
{
    this->ui->tableBooks->selectRow(index.row());
    QList<QStandardItem*> row;
    for (int i = 0;i < this->bookModel->columnCount();i++){
        row << this->bookModel->item(index.row(), i)->clone();
    }
    if (this->mode == 0){
        row.removeAt(2);
        row[0]->setEditable(false);
        row[1]->setEditable(false);
        row[2]->setEditable(false);
        QStandardItem *quantity = new QStandardItem();
        quantity->setText(QString::number(1));
        QStandardItem *numOfDay = new QStandardItem();
        numOfDay->setText(QString::number(1));
        QStandardItem *money = new QStandardItem();
        money->setText(QString::number(1));
        row.append(quantity);
        row.append(numOfDay);
        row.append(money);
        // check if book is selected
        for (int i = 0;i < this->selectedBookModel->rowCount();i++){
            if (this->selectedBookModel->item(i, 0)->text() == row[0]->text()){
                this->showMessageBox(QString::fromUtf8("Thông báo"), QString::fromUtf8("Sách này đã được chọn trước đó"), QString::fromUtf8(""));
                return;
            }

        }
    }
    this->selectedBookModel->appendRow(row);
    this->bookModel->removeRow(index.row());

}

void MainWindow::on_tableSeletedBooks_doubleClicked(const QModelIndex &index)
{
    this->ui->tableSeletedBooks->selectRow(index.row());
    QList<QStandardItem*> row;
    for (int i = 0;i < this->selectedBookModel->columnCount();i++){
        row << this->selectedBookModel->item(index.row(), i)->clone();
    }
    if (this->mode == 1)
        this->bookModel->appendRow(row);
    this->selectedBookModel->removeRow(index.row());
}

void MainWindow::on_btnReturnBook_clicked()
{
    if (this->mode != 1 || this->selectedBookModel->rowCount() == 0){
        this->showMessageBox(QString::fromUtf8("Thông báo"), QString::fromUtf8("Chưa tải danh sách sách đã mượn"), QString::fromUtf8("Vui lòng chọn tài khoản và chọn sách cần trả"));
        return;
    }
    UserService* userService = UserService::initUserService();
    Listt<int> *listId = new LinkedListt<int>;
    for (int i = 0;i < this->selectedBookModel->rowCount();i++){
        int id = this->selectedBookModel->item(i)->text().toInt();
        listId->add(id);
    }
    int result = userService->returnBook(listId);
    int tmp = result;
    if (result == -1){
        this->selectedBookModel->clear();
    } else {
        while (result > 0){
            result--;
            this->selectedBookModel->removeRow(0);
        }
        this->showMessageBox(QString::fromUtf8("Thông báo"), QString::fromUtf8("Đã xảy ra lỗi"), QString::fromUtf8("Không thể trả sách với ID = ") + QString::number(listId->get(tmp)));
        return;
    }

}

void MainWindow::on_menuAdminShowUsers_triggered()
{
    ManageUser *manageUser = new ManageUser(NULL, this->sessionUser);
    manageUser->show();
    this->hide();
    if (manageUser->exec() == QDialog::Rejected) {
       manageUser->close();
       delete manageUser;
       this->show();
    }

}

// Show dialog Chức năng quản lý sách
void MainWindow::on_menuAdminShowBook_triggered()
{
    managebook *manageBook = new managebook();
    manageBook->show();
    this->hide();
    if (manageBook->exec() == QDialog::Rejected) {
       manageBook->close();
       this->show();
       delete manageBook;
    }
}

void MainWindow::on_menuLogout_triggered()
{
    this->sessionUser = NULL;
    this->login();
}

int MainWindow::showMessageBox(QString title, QString text, QString info){
    this->msgBox->setWindowTitle(title);
    this->msgBox->setText(text);
    this->msgBox->setInformativeText(info);
    return this->msgBox->exec();
}

void MainWindow::on_menuUserInfo_triggered()
{
    QString info = "";
    info += QString::fromUtf8("Họ và tên: ") + this->sessionUser->getFullname() + "\n"
            + QString::fromUtf8("Ngày sinh: ") + this->sessionUser->getBirthday().toString("dd/MM/yyyy") + "\n"
            + QString::fromUtf8("Giới tính: ") + (this->sessionUser->getGender() == 0 ? "Nam" : (this->sessionUser->getGender() == 1 ? "Nữ" : "Không xác định")) + "\n"
            + QString::fromUtf8("Địa chỉ: ") + this->sessionUser->getAddress() + "\n"
            + QString::fromUtf8("Quyền: ") + this->sessionUser->getRole().getDescription() + "\n"
            + QString::fromUtf8("Điện thoại: ") + this->sessionUser->getPhone() + "\n"
            + QString::fromUtf8("Email: ") + this->sessionUser->getEmail() + "\n"
            + QString::fromUtf8("Tài khoản: ") + this->sessionUser->getUsername();
    this->showMessageBox(QString::fromUtf8("Thông tin"), QString::fromUtf8("Thông tin tài khoản:"), info);
}

void MainWindow::on_actionTh_ng_tin_quy_n_triggered()
{

    if (this->sessionUser->getRole().getPriorty() != 0)
    {
        this->showMessageBox(QString::fromUtf8("Thống báo"), QString::fromUtf8("Lỗi quyền truy cập"), QString::fromUtf8("Tính năng này chỉ dành cho quyền cao nhất"));
        return;
    }

    ManageRole *manageRole = new ManageRole();
    manageRole->show();
    this->hide();
    if (manageRole->exec() == QDialog::Rejected)
    {
       manageRole->close();
       delete manageRole;
       this->show();
    }
}

// Show dialog CRUD Publisher
void MainWindow::on_menu_publisher_triggered()
{
    ManagePublisher* mangePublisher = new ManagePublisher();
    mangePublisher->show();
    this->hide();
    if (mangePublisher->exec() == QDialog::Rejected) {
       mangePublisher->close();
       delete mangePublisher;
       this->show();
    }
}

void MainWindow::on_menu_category_triggered()
{
    ManageCategory* manageCategory = new ManageCategory();
    manageCategory->show();
    this->hide();
    if (manageCategory->exec() == QDialog::Rejected) {
       manageCategory->close();
       delete manageCategory;
       this->show();
    }
}

void MainWindow::on_menu_issuing_company_triggered()
{
    ManageIssuingCompany* manageIssuingCompany = new ManageIssuingCompany();
    manageIssuingCompany->show();
    this->hide();
    if (manageIssuingCompany->exec() == QDialog::Rejected) {
       manageIssuingCompany->close();
       delete manageIssuingCompany;
       this->show();
    }
}

void MainWindow::on_btnBorrowBook_clicked()
{
    if (this->selectedUser == nullptr){
        this->showMessageBox(QString::fromUtf8("Thông báo"), QString::fromUtf8("Chưa chọn tài khoản"), QString::fromUtf8("Vui lòng chọn tài khoản cần mượn sách"));
        return;
    }

    if (this->mode != 0 || this->selectedBookModel->rowCount() == 0){
        this->showMessageBox(QString::fromUtf8("Thông báo"), QString::fromUtf8("Chưa tải danh sách sách để mượn"), QString::fromUtf8("Vui lòng chọn tài khoản và chọn sách cần mượn"));
        return;
    }

    UserService* userService = UserService::initUserService();
    Listt<BorrowBook> *list = this->getDataBorrow();
    try{
        userService->borrowBook(list);
        this->clearData();
    } catch (QString &error){
        this->showMessageBox(QString::fromUtf8("Thông báo"), QString::fromUtf8("Dữ liệu mượn sách không hợp lệ"), error);
    } catch (...){
        this->showMessageBox(QString::fromUtf8("Thông báo"), QString::fromUtf8("Xảy ra lỗi"), QString::fromUtf8("Lỗi không xác định") );
    }
}

void MainWindow::on_actionT_c_gi_triggered()
{
    Manage_Author* manageAuthor = new Manage_Author();
    manageAuthor->show();
    this->hide();
    if (manageAuthor->exec() == QDialog::Rejected) {
       manageAuthor->close();
       delete manageAuthor;
       this->show();
    }
}
//
void MainWindow::on_tableSeletedBooks_pressed(const QModelIndex &index)
{
    //this->selectedBookModel->removeRow(index.row());
}

Listt<BorrowBook>* MainWindow::getDataBorrow(){
    Listt<BorrowBook> *listBorrow = new LinkedListt<BorrowBook>();
    for (int i = 0;i < this->selectedBookModel->rowCount();i++){
        int id = this->selectedBookModel->item(i, 0)->text().toInt();
        int available = this->selectedBookModel->item(i, 2)->text().toInt();
        int quantity = this->selectedBookModel->item(i, 3)->text().toInt();
        int numOfDay = this->selectedBookModel->item(i, 4)->text().toInt();
        int money = this->selectedBookModel->item(i, 5)->text().toInt();
        int user_id = this->selectedUser->getUserId();
        Book book(id, available);
        BorrowBook item(-1, user_id, book,  quantity, numOfDay, money);
        listBorrow->add(item);
    }
    return listBorrow;

}
void MainWindow::clearData(){
    this->ui->textUserInfo->setText(QString::fromUtf8("Chưa chọn tài khoản"));
    this->selectedBookModel->clear();
    this->selectedUser = nullptr;
    this->bookModel->clear();
    this->userModel->clear();
}
