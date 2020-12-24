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
    this->insertedAuthorList = new LinkedListt<Author>();
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

// Tìm kiếm
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

// Đổ dữ liệu từ right table qua left form
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

        QStandardItemModel *model = new QStandardItemModel();
        QStringList horizontalHeader;
        horizontalHeader.append("Id");
        horizontalHeader.append(QString::fromUtf8("Tên"));
        ui->list_book_author->setModel(model);
        Listt<Author>* authorList = book.getAuthors();
        for (int i = 0; i < authorList->getSize(); i++) {
            Author author = authorList->get(i);
            QStandardItem *idCol = new QStandardItem(QString::number(author.getId()));
            QStandardItem *nameCol = new QStandardItem(author.getName());
            model->appendRow( QList<QStandardItem*>() << idCol << nameCol);
        }

        this->insertedCategory = *(this->currentBook.getCategory());
        this->insertedPublisher = *(this->currentBook.getPublisher());
        this->insertedIssuingCompany = *(this->currentBook.getIssuingCompany());
//        this->insertedAuthorList = book.getAuthors();
        this->insertedAuthorList->clear();
        for (int i = 0; i < book.getAuthors()->getSize(); i++)
        {
            this->insertedAuthorList->add(book.getAuthors()->get(i));
        }
    }
}

// Dialog cập nhật Publisher cho Book
void managebook::on_btn_change__book_publisher_clicked()
{
    int idx = this->getIndexRow();

    // Nếu người dùng có double click vào bảng bên phải(danh sách các sách)
    if (idx >= 0) {
        Book book = this->bookList->get(idx);

        ChangeBookPublisher *changeBookPublisherUi = new ChangeBookPublisher();
        changeBookPublisherUi->show();
        int x = changeBookPublisherUi->exec();
        if (x == QDialog::Rejected)
        {
            changeBookPublisherUi->close();
            delete changeBookPublisherUi;
        }
        else if(x == QDialog::Accepted)
        {
            changeBookPublisherUi->close();
            Publisher publisher = changeBookPublisherUi->getPublisher();

            if (publisher.getId() >= 0)
            {
                 if (publisher.getId() != this->currentBook.getPublisher()->getId())
                 {
                     Publisher* myPublisher = new Publisher(publisher);
                     this->currentBook.setPublisher(myPublisher);
                     ui->input_book_publisher->setText(publisher.getName());
                 }
                 this->insertedPublisher = publisher;
            }
            delete changeBookPublisherUi;
        }
    } else
    {
        ChangeBookPublisher *changeBookPublisherUi = new ChangeBookPublisher();
        changeBookPublisherUi->show();

        int x = changeBookPublisherUi->exec();
        if (x == QDialog::Rejected)
        {
            changeBookPublisherUi->close();
            delete changeBookPublisherUi;
        }
        else if(x == QDialog::Accepted)
        {
            changeBookPublisherUi->close();
            this->insertedPublisher = changeBookPublisherUi->getPublisher();
            ui->input_book_publisher->setText(this->insertedPublisher.getName());

            delete changeBookPublisherUi;
        }
    }
}

// Reset left-form
void managebook::on_btn_reset_book_clicked()
{
    this->setIndexRow(-1);
    Book book;
    this->setCurrentBook(book);

    ui->input_book_id->setText("");
    ui->input_book_title->setText("");
    ui->input_book_total->setText(0);
    ui->input_book_available->setText(0);
    ui->input_book_price->setText(0);
    ui->input_book_cover->setText("");
    ui->input_book_publication->setDate(QDate::currentDate());
    ui->input_book_publisher->setText("");
    ui->input_book_category->setText("");
    ui->input_book_issuing_company_2->setText("");

    this->insertedAuthorList = new LinkedListt<Author>();
    this->insertedCategory = Category();
    this->insertedIssuingCompany = IssuingCompany();
    this->insertedPublisher = Publisher();
    this->insertedBook = Book();

    QStandardItemModel *model = new QStandardItemModel();
    QStringList horizontalHeader;
    horizontalHeader.append("Id");
    horizontalHeader.append(QString::fromUtf8("Tên"));
    ui->list_book_author->setModel(model);
}

// Câp nhật sách
void managebook::on_btn_update_book_clicked()
{
    QMessageBox *msgBox = new QMessageBox(0);
    msgBox->setWindowTitle(QString::fromUtf8("Thông báo"));
    msgBox->setText(QString::fromUtf8("Bạn có muốn cập nhật?"));
    msgBox->setInformativeText(QString::fromUtf8("Vui lòng kiểm tra lại chính xác thông tin trước khi cập nhật!"));
    msgBox->setStandardButtons(QMessageBox::Ok | QMessageBox::Cancel);
    msgBox->setDefaultButton(QMessageBox::Ok);
    int ret = msgBox->exec();
    if (ret == QMessageBox::Ok) {
        if (this->currentBook.getId() >= 0) {
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

            if (!validateInput(title, coverType, price, total, available, issuing_company_id, publisher_id, category_id))
            {
                QMessageBox *failBox = new QMessageBox(0);
                failBox->setWindowTitle(QString::fromUtf8("Thông báo"));
                failBox->setText(QString::fromUtf8("Có lỗi xảy ra"));
                failBox->setInformativeText(QString::fromUtf8("Kiểu dữ liệu không hợp lệ."));
                failBox->exec();
                return;
            }

            Book updatedBook(id, title, coverType, price, total, available, publication_date,
                             size, number_of_pages, issuing_company_id, publisher_id,
                             category_id, created_at, updated_at, deleted_at);
            updatedBook.setAnotherAuthorList(this->currentBook.getAuthors());

            if (bookService->updateBook(updatedBook))
            {
                QMessageBox *successBox = new QMessageBox(0);
                successBox->setWindowTitle(QString::fromUtf8("Thông báo"));
                successBox->setText(QString::fromUtf8("Cập nhật thành công"));
                successBox->setInformativeText(QString::fromUtf8("Load lại dữ liệu để thấy thay đổi!"));
                successBox->exec();
            }
            else
            {
                QMessageBox *failBox = new QMessageBox(0);
                failBox->setWindowTitle(QString::fromUtf8("Thông báo"));
                failBox->setText(QString::fromUtf8("Có lỗi xảy ra, dữ liệu có thể không hợp lệ."));
                failBox->setInformativeText(QString::fromUtf8("Vui lòng thử lại!"));
                failBox->exec();
            }
        } else
        {
            QMessageBox *failBox = new QMessageBox(0);
            failBox->setWindowTitle(QString::fromUtf8("Thông báo"));
            failBox->setText(QString::fromUtf8("Có lỗi xảy ra"));
            failBox->setInformativeText(QString::fromUtf8("Kiểu dữ liệu không hợp lệ."));
            failBox->exec();
            return;
        }
    }
}

// show dialog cap nhat category cua book
void managebook::on_btn_change_book_category_clicked()
{
    int idx = this->getIndexRow();

    if (idx >= 0) {
        Book book = this->bookList->get(idx);

        ChangeBookCategory *changeBookCategoryUi = new ChangeBookCategory();
        changeBookCategoryUi->show();

        int x = changeBookCategoryUi->exec();
        if (x == QDialog::Rejected) {
            changeBookCategoryUi->close();
            delete changeBookCategoryUi;
        }
        else if (x == QDialog::Accepted)
        {
            changeBookCategoryUi->close();

            Category category = changeBookCategoryUi->getCategory();

            if (category.getId() >= 0) {
                 if (category.getId() != this->currentBook.getCategory()->getId()) {
                     Category* myCategory = new Category(category);
                     this->currentBook.setCategory(myCategory);
                     ui->input_book_category->setText(myCategory->getName());
                 }
                 this->insertedCategory = category;
            }

            delete changeBookCategoryUi;
        }
    }
    else
    {
        ChangeBookCategory *changeBookCategoryUi = new ChangeBookCategory();
        changeBookCategoryUi->show();

        int x = changeBookCategoryUi->exec();
        if (x == QDialog::Rejected) {
            changeBookCategoryUi->close();
            delete changeBookCategoryUi;
        }
        else if (x == QDialog::Accepted)
        {
            changeBookCategoryUi->close();
            this->insertedCategory = changeBookCategoryUi->getCategory();
            ui->input_book_category->setText(this->insertedCategory.getName());
            delete changeBookCategoryUi;
        }
    }
}

// show dialog cap nhat issuing company cua book
void managebook::on_btn_change_book_issuing_compan_clicked()
{
    int idx = this->getIndexRow();

    if (idx >= 0) {
        Book book = this->bookList->get(idx);

        ChangeBookIssuingCompany *changeBookIssuingCompany = new ChangeBookIssuingCompany();
        changeBookIssuingCompany->show();

        int x = changeBookIssuingCompany->exec();
        if (x == QDialog::Rejected) {
            changeBookIssuingCompany->close();
            delete changeBookIssuingCompany;
        }
        else if (x == QDialog::Accepted)
        {
            changeBookIssuingCompany->close();

            IssuingCompany issuingCompany = changeBookIssuingCompany->getIssuingCompany();

            if (issuingCompany.getId() >= 0) {
                 if (issuingCompany.getId() != this->currentBook.getIssuingCompany()->getId()) {
                     IssuingCompany* myIssuingCompany = new IssuingCompany(issuingCompany);
                     this->currentBook.setIssuingCompany(myIssuingCompany);
                     ui->input_book_issuing_company_2->setText(myIssuingCompany->getName());
                 }
                 this->insertedIssuingCompany = issuingCompany;
            }

            delete changeBookIssuingCompany;
        }
    }
    else
    {
        ChangeBookIssuingCompany *changeBookIssuingCompany = new ChangeBookIssuingCompany();
        changeBookIssuingCompany->show();

        int x = changeBookIssuingCompany->exec();
        if (x == QDialog::Rejected) {
            changeBookIssuingCompany->close();
            delete changeBookIssuingCompany;
        }
        else if (x == QDialog::Accepted)
        {
            changeBookIssuingCompany->close();
            this->insertedIssuingCompany = changeBookIssuingCompany->getIssuingCompany();
            ui->input_book_issuing_company_2->setText(this->insertedIssuingCompany.getName());
            delete changeBookIssuingCompany;
        }
    }
}

// show dialog cap nhat Author cua book
void managebook::on_btn_change_book_authors_clicked()
{
    int idx = this->getIndexRow();

    if (idx >= 0) {
        Book book = this->bookList->get(idx);

        ChangeBookAuthors *changeBookAuthorsUi = new ChangeBookAuthors();

        changeBookAuthorsUi->setCurrentAuthorList(book.getAuthors());

        changeBookAuthorsUi->show();
        int x = changeBookAuthorsUi->exec();

        if (x == QDialog::Rejected) {
           changeBookAuthorsUi->close();
           delete changeBookAuthorsUi;
        }
        else if (x == QDialog::Accepted)
        {
            qDebug() << "merry xmas :(( ";
            changeBookAuthorsUi->close();

            Listt<Author>* authorList = changeBookAuthorsUi->getCurrentAuthorList();
            this->currentBook.getAuthors()->clear();
            this->insertedAuthorList->clear();

            qDebug() << "-- current list";
            for (int i = 0; i < this->currentBook.getAuthors()->getSize(); i++) {
                qDebug() << this->currentBook.getAuthors()->get(i).getName();
            }

            qDebug() << "-- returning list";
            for (int i = 0; i < authorList->getSize(); i++) {
                qDebug() << authorList->get(i).getName();
                this->currentBook.getAuthors()->add(authorList->get(i));
                this->insertedAuthorList->add(authorList->get(i));
            }

            qDebug() << "-- after current list";
            for (int i = 0; i < this->currentBook.getAuthors()->getSize(); i++) {
                qDebug() << this->currentBook.getAuthors()->get(i).getName();
            }

            QStandardItemModel *model = new QStandardItemModel();
            QStringList horizontalHeader;
            horizontalHeader.append("Id");
            horizontalHeader.append(QString::fromUtf8("Tên"));
            ui->list_book_author->setModel(model);

            qDebug() << "-- adding into table";
            for (int i = 0; i < this->currentBook.getAuthors()->getSize(); i++) {
                qDebug() << this->currentBook.getAuthors()->get(i).getName();
                Author author = this->currentBook.getAuthors()->get(i);
                QStandardItem *idCol = new QStandardItem(QString::number(author.getId()));
                QStandardItem *nameCol = new QStandardItem(author.getName());
                model->appendRow( QList<QStandardItem*>() << idCol << nameCol);
            }

            delete changeBookAuthorsUi;
        }
    }
    else
    {
        ChangeBookAuthors *changeBookAuthorsUi = new ChangeBookAuthors();
        changeBookAuthorsUi->setCurrentAuthorList(this->insertedAuthorList);
        changeBookAuthorsUi->show();

        int x = changeBookAuthorsUi->exec();
        if (x == QDialog::Rejected) {
           changeBookAuthorsUi->close();
           delete changeBookAuthorsUi;
        }
        else if (x == QDialog::Accepted)
        {
            changeBookAuthorsUi->close();
            Listt<Author>* authorList = changeBookAuthorsUi->getCurrentAuthorList();
            this->insertedAuthorList->clear();

            for (int i = 0; i < authorList->getSize(); i++) {
                this->insertedAuthorList->add(authorList->get(i));
            }

            QStandardItemModel *model = new QStandardItemModel();
            QStringList horizontalHeader;
            horizontalHeader.append("Id");
            horizontalHeader.append(QString::fromUtf8("Tên"));
            ui->list_book_author->setModel(model);

            for (int i = 0; i < this->insertedAuthorList->getSize(); i++) {
                Author author = this->insertedAuthorList->get(i);
                QStandardItem *idCol = new QStandardItem(QString::number(author.getId()));
                QStandardItem *nameCol = new QStandardItem(author.getName());
                model->appendRow( QList<QStandardItem*>() << idCol << nameCol);
            }

            delete changeBookAuthorsUi;
        }
    }
}

// Thêm mới sách
void managebook::on_btn_add_book_clicked()
{
    QMessageBox *msgBox = new QMessageBox(0);
    msgBox->setWindowTitle(QString::fromUtf8("Thông báo"));
    msgBox->setText(QString::fromUtf8("Bạn có muốn thêm?"));
    msgBox->setInformativeText(QString::fromUtf8("Vui lòng kiểm tra lại chính xác thông tin trước khi thêm!"));
    msgBox->setStandardButtons(QMessageBox::Ok | QMessageBox::Cancel);
    msgBox->setDefaultButton(QMessageBox::Ok);
    int ret = msgBox->exec();
    if (ret == QMessageBox::Ok)
    {
        QString title = ui->input_book_title->text();
        QString coverType = ui->input_book_cover->text();
        float price = ui->input_book_price->text().toFloat();
        int total = ui->input_book_total->text().toInt();
        int available = ui->input_book_available->text().toInt();
        QDate publication_date = ui->input_book_publication->date();

        QString size = "Unknown";
        int number_of_pages = 123;
        int issuing_company_id = this->insertedIssuingCompany.getId();
        int publisher_id = this->insertedPublisher.getId();
        int category_id = this->insertedCategory.getId();
        QDate created_at = QDate::currentDate();

        if (!validateInput(title, coverType, price, total, available, issuing_company_id, publisher_id, category_id))
        {
            QMessageBox *failBox = new QMessageBox(0);
            failBox->setWindowTitle(QString::fromUtf8("Thông báo"));
            failBox->setText(QString::fromUtf8("Có lỗi xảy ra"));
            failBox->setInformativeText(QString::fromUtf8("Dữ liệu không hợp lệ."));
            failBox->exec();
            return;
        }

        Book insertedBook(title, coverType, price, total, available, publication_date,
                         size, number_of_pages, issuing_company_id, publisher_id,
                         category_id, created_at);
        insertedBook.setIssuingCompany(new IssuingCompany(this->insertedIssuingCompany));
        insertedBook.setCategory(new Category(this->insertedCategory));
        insertedBook.setPublisher(new Publisher(this->insertedPublisher));
        insertedBook.setAnotherAuthorList(this->insertedAuthorList);

        BookService *bookService = BookService::initBookService();
        if (bookService->insertBook(insertedBook))
        {
            QMessageBox *successBox = new QMessageBox(0);
            successBox->setWindowTitle(QString::fromUtf8("Thông báo"));
            successBox->setText(QString::fromUtf8("Thêm thành công"));
            successBox->setInformativeText(QString::fromUtf8("Load lại dữ liệu để thấy thay đổi!"));
            successBox->exec();
        }
        else
        {
            QMessageBox *failBox = new QMessageBox(0);
            failBox->setWindowTitle(QString::fromUtf8("Thông báo"));
            failBox->setText(QString::fromUtf8("Có lỗi xảy ra, dữ liệu có thể không hợp lệ."));
            failBox->setInformativeText(QString::fromUtf8("Vui lòng thử lại!"));
            failBox->exec();
        }
    }
}

bool managebook::validateInput(QString title, QString coverType, float price,int total,
                               int available, int issuing_company_id, int publisher_id,
                               int category_id)
{
    if (title.size() == 0 || coverType.size() == 0 || price < 0 || total < 0 || available < 0 || total < available || issuing_company_id < 0 || publisher_id < 0 || category_id < 0)
    {
        return false;
    }
    return true;
}

void managebook::on_btn_delete_book_clicked()
{
    QMessageBox *msgBox = new QMessageBox(0);
    msgBox->setWindowTitle(QString::fromUtf8("Thông báo"));
    msgBox->setText(QString::fromUtf8("Bạn có muốn xóa?"));
    msgBox->setInformativeText(QString::fromUtf8("Vui lòng kiểm tra lại chính xác thông tin trước khi xóa!"));
    msgBox->setStandardButtons(QMessageBox::Ok | QMessageBox::Cancel);
    msgBox->setDefaultButton(QMessageBox::Ok);
    int ret = msgBox->exec();
    if (ret == QMessageBox::Ok)
    {
        int id = this->currentBook.getId();

        BookService *bookService = BookService::initBookService();
        if (bookService->deleteBookById(id))
        {
            QMessageBox *successBox = new QMessageBox(0);
            successBox->setWindowTitle(QString::fromUtf8("Thông báo"));
            successBox->setText(QString::fromUtf8("Xóa thành công"));
            successBox->exec();
            on_btn_reset_book_clicked();
        }
        else
        {
            QMessageBox *failBox = new QMessageBox(0);
            failBox->setWindowTitle(QString::fromUtf8("Thông báo"));
            failBox->setText(QString::fromUtf8("Có lỗi xảy ra hoặc không tìm thấy id"));
            failBox->setInformativeText(QString::fromUtf8("Vui lòng thử lại!"));
            failBox->exec();
        }
    }
}


