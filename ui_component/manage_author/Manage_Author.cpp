#include "Manage_Author.h"
#include "ui_Manage_Author.h"

Manage_Author::Manage_Author(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::Manage_Author)
{
    ui->setupUi(this);
    this->authorList = new LinkedListt<Author>();
    ui->table_author->setEditTriggers(QAbstractItemView::NoEditTriggers);
}

Manage_Author::~Manage_Author()
{
    delete ui;
}


int Manage_Author::getIndexRow()
{
    return this->indexRow;
}

bool Manage_Author::setIndexRow(int idx)
{
    if (idx < 0)
        return false;
    this->indexRow = idx;
    return true;
}

void Manage_Author::resetIndexRow()
{
    this->indexRow = -1;
}

Author Manage_Author::getCurrentAuthor()
{
    return this->currentAuthor;
}

bool Manage_Author::setCurrentAuthor(Author author)
{
    this->currentAuthor = author;
    return true;
}

void Manage_Author::on_btn_search_clicked()
{
     AuthorService* authorService = AuthorService::initAuthorService();

     QString byName = ui->input_search->text();

     // Tìm kiếm theo tên sách
     this->authorList->clear();

     this->authorList = authorService->findAuthorByName(byName);

     QStandardItemModel *model = new QStandardItemModel();
     QStringList horizontalHeader;
     horizontalHeader.append("Id");
     horizontalHeader.append(QString::fromUtf8("Tên"));
     horizontalHeader.append(QString::fromUtf8("Ngày tạo"));
     horizontalHeader.append(QString::fromUtf8("Cập nhật lần cưới"));
     model->setHorizontalHeaderLabels(horizontalHeader);
     ui->table_author->setModel(model);

     for (int i = 0; i < this->authorList->getSize(); i++) {
         Author author = this->authorList->get(i);
         QStandardItem *idCol = new QStandardItem(QString::number(author.getId()));
         QStandardItem *nameCol = new QStandardItem(author.getName());
         QStandardItem *createdAtCol = new QStandardItem(author.getCreatedAt().toString());
         QStandardItem *updatedAtCol = new QStandardItem(author.getUpdatedAt().toString());
         model->appendRow( QList<QStandardItem*>() << idCol << nameCol << createdAtCol << updatedAtCol);
     }
}

void Manage_Author::on_table_author_doubleClicked(const QModelIndex &index)
{
    int idx = index.row();

    if (this->setIndexRow(idx))
    {
        if (this->setCurrentAuthor(this->authorList->get(idx)))
        {
            Author author = this->getCurrentAuthor();
            ui->author_id->setText(QString::number(author.getId()));
            ui->author_name->setText(author.getName());
            ui->author_created_at->setDate(author.getCreatedAt());
            ui->author_updated_at->setDate(author.getDeletedAt());
        }

    }
}

void Manage_Author::on_btn_add_clicked()
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
        QString name = ui->author_name->text();
        QDate createdAt = ui->author_created_at->date();
        QDate updatedAt = ui->author_updated_at->date();

        if (name.size() > 0) {
            AuthorService* authorService = AuthorService::initAuthorService();
            Author author(name, createdAt, updatedAt);

            if (authorService->saveAuthor(author))
            {

                QMessageBox *successBox = new QMessageBox(0);
                successBox->setWindowTitle(QString::fromUtf8("Thông báo"));
                successBox->setText(QString::fromUtf8("Thêm thành công"));
                successBox->exec();
                on_btn_reset_clicked();
            }
            else
            {
                QMessageBox *failBox = new QMessageBox(0);
                failBox->setWindowTitle(QString::fromUtf8("Thông báo"));
                failBox->setText(QString::fromUtf8("Có lỗi xảy ra, kiểu dữ liệu có thể không hợp lệ."));
                failBox->setInformativeText(QString::fromUtf8("Vui lòng thử lại!"));
                failBox->exec();
            }
        }
        else
        {
            QMessageBox *failBox = new QMessageBox(0);
            failBox->setWindowTitle(QString::fromUtf8("Thông báo"));
            failBox->setText(QString::fromUtf8("Có lỗi xảy ra, kiểu dữ liệu có thể không hợp lệ."));
            failBox->setInformativeText(QString::fromUtf8("Vui lòng thử lại!"));
            failBox->exec();
        }
    }
}

void Manage_Author::on_btn_update_clicked()
{
    QMessageBox *msgBox = new QMessageBox(0);
    msgBox->setWindowTitle(QString::fromUtf8("Thông báo"));
    msgBox->setText(QString::fromUtf8("Bạn có muốn cập nhật?"));
    msgBox->setInformativeText(QString::fromUtf8("Vui lòng kiểm tra lại chính xác thông tin trước khi cập nhật!"));
    msgBox->setStandardButtons(QMessageBox::Ok | QMessageBox::Cancel);
    msgBox->setDefaultButton(QMessageBox::Ok);
    int ret = msgBox->exec();
    if (ret == QMessageBox::Ok)
    {
        if (this->currentAuthor.getId() >= 0)
        {
            int id = this->currentAuthor.getId();

            QString name = ui->author_name->text();
            QDate createdAt = ui->author_created_at->date();
            QDate updatedAt = ui->author_updated_at->date();

            Author author(id, name, createdAt, updatedAt);

            AuthorService* authorService = AuthorService::initAuthorService();

            if (authorService->updateAuthor(author))
            {
                QMessageBox *successBox = new QMessageBox(0);
                successBox->setWindowTitle(QString::fromUtf8("Thông báo"));
                successBox->setText(QString::fromUtf8("Cập nhật thành công"));
                successBox->exec();
                on_btn_reset_clicked();
            }
            else
            {
                QMessageBox *failBox = new QMessageBox(0);
                failBox->setWindowTitle(QString::fromUtf8("Thông báo"));
                failBox->setText(QString::fromUtf8("Có lỗi xảy ra, có thể id không tồn tại"));
                failBox->setInformativeText(QString::fromUtf8("Vui lòng thử lại!"));
                failBox->exec();
            }
        }
        else
        {
            QMessageBox *failBox = new QMessageBox(0);
            failBox->setWindowTitle(QString::fromUtf8("Thông báo"));
            failBox->setText(QString::fromUtf8("Có lỗi xảy ra, có thể id không tồn tại"));
            failBox->setInformativeText(QString::fromUtf8("Vui lòng thử lại!"));
            failBox->exec();
        }
    }
}

void Manage_Author::on_btn_delete_clicked()
{
    Author author = this->currentAuthor;

    QMessageBox *msgBox = new QMessageBox(0);
    msgBox->setWindowTitle(QString::fromUtf8("Thông báo"));
    msgBox->setText(QString::fromUtf8("Bạn có muốn xóa?"));
    msgBox->setInformativeText(QString::fromUtf8("Vui lòng kiểm tra lại chính xác thông tin trước khi xóa!"));
    msgBox->setStandardButtons(QMessageBox::Ok | QMessageBox::Cancel);
    msgBox->setDefaultButton(QMessageBox::Ok);
    int ret = msgBox->exec();
    if (ret == QMessageBox::Ok)
    {
        if (author.getId() >= 0)
        {
            AuthorService* authorService = AuthorService::initAuthorService();
            if (authorService->deleteAuthorById(author.getId()))
            {
                QMessageBox *successBox = new QMessageBox(0);
                successBox->setWindowTitle(QString::fromUtf8("Thông báo"));
                successBox->setText(QString::fromUtf8("Xóa thành công"));
                successBox->exec();
                on_btn_reset_clicked();
            }
            else
            {
                QMessageBox *failBox = new QMessageBox(0);
                failBox->setWindowTitle(QString::fromUtf8("Thông báo"));
                failBox->setText(QString::fromUtf8("Có lỗi xảy ra, có thể id không tồn tại"));
                failBox->setInformativeText(QString::fromUtf8("Vui lòng thử lại!"));
                failBox->exec();
            }

        }
        else
        {
            QMessageBox *failBox = new QMessageBox(0);
            failBox->setWindowTitle(QString::fromUtf8("Thông báo"));
            failBox->setText(QString::fromUtf8("Có lỗi xảy ra, có thể id không tồn tại"));
            failBox->setInformativeText(QString::fromUtf8("Vui lòng thử lại!"));
            failBox->exec();
        }
    }
}

void Manage_Author::on_btn_reset_clicked()
{
    this->currentAuthor = Author();
    this->resetIndexRow();

    ui->author_id->setText("");
    ui->author_name->setText("");
    ui->author_created_at->setDate(QDate::currentDate());
    ui->author_updated_at->setDate(QDate::currentDate());
}
