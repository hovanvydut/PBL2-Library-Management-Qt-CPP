#include "ChangeBookAuthors.h"
#include "ui_ChangeBookAuthors.h"

ChangeBookAuthors::ChangeBookAuthors(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::ChangeBookAuthors)
{
    ui->setupUi(this);

    this->currentAuthorList = new LinkedListt<Author>();
    this->allAuthorList = new LinkedListt<Author>();

    ui->table_author->setEditTriggers(QAbstractItemView::NoEditTriggers);
    ui->table_current_author->setEditTriggers(QAbstractItemView::NoEditTriggers);

    this->currentAuthorModelUi = new QStandardItemModel();
    QStringList horizontalHeader;
    horizontalHeader.append("Id");
    horizontalHeader.append(QString::fromUtf8("Tên"));
    ui->table_current_author->setModel(this->currentAuthorModelUi);

}

ChangeBookAuthors::~ChangeBookAuthors()
{
    delete ui;
}

Listt<Author>* ChangeBookAuthors::getCurrentAuthorList()
{
    return this->currentAuthorList;
}

void ChangeBookAuthors::setCurrentAuthorList(Listt<Author>* list)
{

    this->currentAuthorList->clear();
    for (int i = 0; i < list->getSize(); i++) {
        Author author = list->get(i);

        this->currentAuthorList->add(author);

        QStandardItem *idCol = new QStandardItem(QString::number(author.getId()));
        QStandardItem *nameCol = new QStandardItem(author.getName());
        this->currentAuthorModelUi->appendRow( QList<QStandardItem*>() << idCol << nameCol);

    }
}

int ChangeBookAuthors::getIndexRow()
{
    return this->indexRow;
}

void ChangeBookAuthors::setIndexRow(int idx)
{
    this->indexRow = idx;
}

void ChangeBookAuthors::on_btn_search_clicked()
{
    QString searchValue = ui->input_search_author->text();
    AuthorService *authorService = AuthorService::initAuthorService();
    this->allAuthorList->clear();
    this->allAuthorList = authorService->findAuthorByName(searchValue);

    QStandardItemModel *model = new QStandardItemModel();
    QStringList horizontalHeader;
    horizontalHeader.append("Id");
    horizontalHeader.append(QString::fromUtf8("Tên"));
    horizontalHeader.append(QString::fromUtf8("Ngày tạo"));
    horizontalHeader.append(QString::fromUtf8("Cập nhật lần cuối"));
    horizontalHeader.append(QString::fromUtf8("Xóa mềm"));
    model->setHorizontalHeaderLabels(horizontalHeader);
    ui->table_author->setModel(model);

    for (int i = 0; i < this->allAuthorList->getSize(); i++) {
        Author author = this->allAuthorList->get(i);
        QStandardItem *idCol = new QStandardItem(QString::number(author.getId()));
        QStandardItem *nameCol = new QStandardItem(author.getName());
        QStandardItem *created_at = new QStandardItem(author.getCreatedAt().toString("dd.MM.yyyy"));
        QStandardItem *updated_at = new QStandardItem(author.getUpdatedAt().toString("dd.MM.yyyy"));
        model->appendRow( QList<QStandardItem*>() << idCol << nameCol << created_at << updated_at);
    }
}

void ChangeBookAuthors::on_table_author_doubleClicked(const QModelIndex &index)
{
    int idx = index.row();

    if (idx >= 0) {
        Author author = this->allAuthorList->get(idx);

        if (!this->currentAuthorList->contains(author))
        {
            this->currentAuthorList->add(author);
            this->setIndexRow(idx);

            QStandardItem *idCol = new QStandardItem(QString::number(author.getId()));
            QStandardItem *nameCol = new QStandardItem(author.getName());
            this->currentAuthorModelUi->appendRow( QList<QStandardItem*>() << idCol << nameCol);
        }

    }
}

void ChangeBookAuthors::on_table_current_author_doubleClicked(const QModelIndex &index)
{
    int idx = index.row();

    if (idx >= 0 && (idx <= (this->currentAuthorList->getSize() - 1))) {
        if (this->currentAuthorList->removeAt(idx)) {
            ui->table_current_author->model()->removeRow(idx);
        }
    }

}

void ChangeBookAuthors::on_btn_update_clicked()
{
    this->accept();
}
