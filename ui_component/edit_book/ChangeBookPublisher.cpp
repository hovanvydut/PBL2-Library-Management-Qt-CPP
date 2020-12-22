#include "ChangeBookPublisher.h"
#include "ui_changebookpublisher.h"

ChangeBookPublisher::ChangeBookPublisher(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::ChangeBookPublisher)
{
    ui->setupUi(this);
    ui->table_publisher->setEditTriggers(QAbstractItemView::NoEditTriggers);
}

ChangeBookPublisher::~ChangeBookPublisher()
{
    delete ui;
}

Publisher ChangeBookPublisher::getPublisher()
{
    return this->publisher;
}

void ChangeBookPublisher::setPublisher(Publisher publisher)
{
    this->publisher = publisher;
}

int ChangeBookPublisher::getIndexRow()
{
    return this->indexRow;
}

void ChangeBookPublisher::setIndexRow(int idx)
{
    this->indexRow = idx;
}

void ChangeBookPublisher::on_btn_search_clicked()
{
    QString searchValue = ui->input_search_publisher->text();
    PublisherService *publisherService = PublisherService::initPublisherService();
    this->publisherList = publisherService->findByName(searchValue);

    QStandardItemModel *model = new QStandardItemModel();
    QStringList horizontalHeader;
    horizontalHeader.append("Id");
    horizontalHeader.append(QString::fromUtf8("Tên"));
    horizontalHeader.append(QString::fromUtf8("Ngày tạo"));
    horizontalHeader.append(QString::fromUtf8("Cập nhật lần cuối"));
    horizontalHeader.append(QString::fromUtf8("Xóa mềm"));
    model->setHorizontalHeaderLabels(horizontalHeader);
    ui->table_publisher->setModel(model);

    for (int i = 0; i < this->publisherList->getSize(); i++) {
        Publisher publisher = this->publisherList->get(i);
        QStandardItem *idCol = new QStandardItem(QString::number(publisher.getId()));
        QStandardItem *nameCol = new QStandardItem(publisher.getName());
        QStandardItem *created_at = new QStandardItem(publisher.getCreatedAt().toString("dd.MM.yyyy"));
        QStandardItem *updated_at = new QStandardItem(publisher.getUpdatedAt().toString("dd.MM.yyyy"));
        model->appendRow( QList<QStandardItem*>() << idCol << nameCol << created_at << updated_at);
    }
}

void ChangeBookPublisher::on_table_publisher_doubleClicked(const QModelIndex &index)
{
    ui->table_publisher->setEditTriggers(QAbstractItemView::NoEditTriggers);
    int idx = index.row();

    if (idx >= 0) {
        Publisher publisher = this->publisherList->get(idx);

        this->setPublisher(publisher);
        this->setIndexRow(idx);

        ui->current_publisher->setText(publisher.getName());
    }
}

void ChangeBookPublisher::on_btn_update_clicked()
{
    this->accept();
}
