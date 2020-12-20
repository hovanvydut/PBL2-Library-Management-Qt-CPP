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
}

managebook::~managebook()
{
    this->bookList->clear();
    delete this->bookList;
    delete ui;
}

void managebook::setIndexRow(int index) {
    this->indexRow = index;
}

int managebook::getIndexRow() {
    return this->indexRow;
}

// Chức năng tìm kiếm
void managebook::on_btn_search_clicked()
{
    this->bookList->clear();

    BookService* bookService = BookService::initBookService();

    QString title = ui->input_search->text();

    // Tìm kiếm theo tên sách
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
    this->setIndexRow(idx);

    if (idx >= 0) {
        Book book = this->bookList->get(idx);
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
        this->hide();
        if (changeBookPublisherUi->exec() == QDialog::Rejected) {
           changeBookPublisherUi->close();
           delete changeBookPublisherUi;
           this->show();
        }
    }
}

// Reset noi dung de nhap lai
void managebook::on_btn_reset_book_clicked()
{
    this->setIndexRow(-1);
}
