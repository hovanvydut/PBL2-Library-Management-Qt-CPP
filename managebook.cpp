#include "managebook.h"
#include "ui_managebook.h"
#include "src/Book/BookService.h"
#include <QStandardItem>
#include <QModelIndex>
#include "ui_component/edit_book/ChangeBookPublisher.h"

managebook::managebook(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::managebook)
{
    ui->setupUi(this);
    this->bookList = new LinkedListt<Book>();
    ui->table_book->setEditTriggers(QAbstractItemView::NoEditTriggers);
    this->bridgeProps = BridgeManageBookUpdateProp::getInstance();
}

managebook::~managebook()
{
    this->bookList->clear();
    delete this->bookList;
    delete ui;
}

void managebook::setIndexRow(int index)
{
    this->indexRow = index;
}

int managebook::getIndexRow()
{
    return this->indexRow;
}

void managebook::setCurrentBook(Book book)
{
    this->currentBook = book;
}

Book managebook::getCurrentBook()
{
    return this->currentBook;
}

// Chức năng tìm kiếm
void managebook::on_btn_search_clicked()
{
    this->bookList->clear();

    BookService* bookService = BookService::initBookService();

    QString title = ui->input_search->text();

    // Tìm kiếm theo tên sách
    this->bookList->clear();
    this->bookList = bookService->findByBookTitle2(title);

    QStandardItemModel *model = new QStandardItemModel();
    QStringList horizontalHeader;
    horizontalHeader.append("Id");
    horizontalHeader.append(QString::fromUtf8("Tên sách"));
    horizontalHeader.append(QString::fromUtf8("Tổng số"));
    horizontalHeader.append(QString::fromUtf8("Hiện có"));
    model->setHorizontalHeaderLabels(horizontalHeader);
    ui->table_book->setModel(model);

    for (int i = 0; i < this->bookList->getSize(); i++) {
        Book book = this->bookList->get(i);
        QStandardItem *idCol = new QStandardItem(QString::number(book.getId()));
        QStandardItem *nameCol = new QStandardItem(book.getTitle());
        QStandardItem *total = new QStandardItem(QString::number(book.getTotal()));
        QStandardItem *available = new QStandardItem(QString::number(book.getAvailable()));
        model->appendRow( QList<QStandardItem*>() << idCol << nameCol << total << available);
    }
}

// Đổ dữ liệu sang table khi double click vào listView
void managebook::on_table_book_doubleClicked(const QModelIndex &index)
{
    int idx = index.row();

    if (idx >= 0) {

        Book book = this->bookList->get(idx);

        this->setCurrentBook(book);
        this->setIndexRow(idx);

        ui->input_book_id->setText(QString::number(book.getId()));
        ui->input_book_title->setText(book.getTitle());
        ui->input_book_total->setText(QString::number(book.getTotal()));
        ui->input_book_available->setText(QString::number(book.getAvailable()));
        ui->input_book_price->setText(QString::number(book.getPrice()));
        ui->input_book_cover->setText(book.getCoverType());
        ui->input_book_publication->setDate(book.getPublicationDate());
        ui->input_book_publisher->setText(book.getPublisher()->getName());
        ui->input_book_category->setText(book.getCategory()->getName());
        ui->input_book_issuing_company_2->setText(book.getIssuingCompany()->getName());
    }
}

void managebook::on_btn_change__book_publisher_clicked()
{
    int idx = this->getIndexRow();

    if (idx >= 0) {
        Book book = this->bookList->get(idx);

        ChangeBookPublisher *changeBookPublisherUi = new ChangeBookPublisher();
        changeBookPublisherUi->show();
//        this->hide();
        if (changeBookPublisherUi->exec() == QDialog::Rejected) {
           changeBookPublisherUi->close();

           Publisher publisher = changeBookPublisherUi->getPublisher();

           if (publisher.getId() >= 0) {
                if (publisher.getId() != this->currentBook.getPublisher()->getId()) {
                    Publisher* myPublisher = new Publisher(publisher);
                    this->currentBook.setPublisher(myPublisher);
                    ui->input_book_publisher->setText(publisher.getName());
                }
           }

           delete changeBookPublisherUi;
//           this->show();
        }
    }
}

// Reset noi dung de nhap lai
void managebook::on_btn_reset_book_clicked()
{
    this->setIndexRow(-1);
}

// Cap nhat sach
void managebook::on_btn_update_book_clicked()
{
    qDebug() << "test";
    QMessageBox *msgBox = new QMessageBox(0);
    msgBox->setWindowTitle(QString::fromUtf8("Thông báo"));
    msgBox->setText(QString::fromUtf8("Bạn có muốn cập nhật?"));
    msgBox->setInformativeText(QString::fromUtf8("Vui lòng kiểm tra lại chính xác thông tin trước khi cập nhật!"));
    if (msgBox->exec() == QMessageBox::Ok) {
        qDebug() << "abc";
        if (this->currentBook.getId() >= 0) {
            qDebug() << "hehre";
            BookService *bookService = BookService::initBookService();

            int id = this->currentBook.getId();
            QString title = ui->input_book_title->text();
            QString coverType = ui->input_book_cover->text();
            float price = ui->input_book_price->text().toFloat();
            int total = ui->input_book_total->text().toInt();
            int available = ui->input_book_available->text().toInt();
            QDate publication_date = ui->input_book_publication->date();
            QString size = this->currentBook.getSize();
            int number_of_pages = this->currentBook.getNumberOfPages();
            int issuing_company_id = this->currentBook.getIssuingCompanyId();
            int publisher_id = this->currentBook.getPublisherId();
            int category_id = this->currentBook.getCategoryId();
            QDate created_at = this->currentBook.getCreatedAt();
            QDate updated_at = this->currentBook.getUpdatedAt();
            QDate deleted_at = this->currentBook.getDeletedAt();

            Book updatedBook(id, title, coverType, price, total, available, publication_date,
                             size, number_of_pages, issuing_company_id, publisher_id,
                             category_id, created_at, updated_at, deleted_at);

            bookService->updateBook(updatedBook);
        }
    }
}
