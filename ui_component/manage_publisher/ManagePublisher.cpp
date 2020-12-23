#include "ManagePublisher.h"
#include "ui_ManagePublisher.h"

ManagePublisher::ManagePublisher(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::ManagePublisher)
{
    ui->setupUi(this);
    ui->table_publisher->setEditTriggers(QAbstractItemView::NoEditTriggers);
    this->publisherList = new LinkedListt<Publisher>();
}

ManagePublisher::~ManagePublisher()
{
    delete ui;
}

int ManagePublisher::getIndexRow()
{
    return this->indexRow;
}

bool ManagePublisher::setIndexRow(int idx)
{
    if (idx < 0)
        return false;
    this->indexRow = idx;
    return true;
}

void ManagePublisher::resetIndexRow()
{
    this->indexRow = -1;
}

Publisher ManagePublisher::getCurrentPublisher()
{
    return this->currentPublisher;
}

bool ManagePublisher::setCurrentPublisher(Publisher publisher)
{
    this->currentPublisher = publisher;
    return true;
}

void ManagePublisher::on_btn_search_clicked()
{
   PublisherService* publisherService = PublisherService::initPublisherService();

    QString byName = ui->input_search->text();

    // Tìm kiếm theo tên sách
    this->publisherList->clear();

    this->publisherList = publisherService->findByName(byName);

    QStandardItemModel *model = new QStandardItemModel();
    QStringList horizontalHeader;
    horizontalHeader.append("Id");
    horizontalHeader.append(QString::fromUtf8("Tên"));
    horizontalHeader.append(QString::fromUtf8("Ngày tạo"));
    horizontalHeader.append(QString::fromUtf8("Cập nhật lần cưới"));
    model->setHorizontalHeaderLabels(horizontalHeader);
    ui->table_publisher->setModel(model);

    for (int i = 0; i < this->publisherList->getSize(); i++) {
        Publisher publisher = this->publisherList->get(i);
        QStandardItem *idCol = new QStandardItem(QString::number(publisher.getId()));
        QStandardItem *nameCol = new QStandardItem(publisher.getName());
        QStandardItem *createdAtCol = new QStandardItem(publisher.getCreatedAt().toString());
        QStandardItem *updatedAtCol = new QStandardItem(publisher.getUpdatedAt().toString());
        model->appendRow( QList<QStandardItem*>() << idCol << nameCol << createdAtCol << updatedAtCol);
    }
}

void ManagePublisher::on_table_publisher_doubleClicked(const QModelIndex &index)
{
    int idx = index.row();

    if (this->setIndexRow(idx))
    {
        if (this->setCurrentPublisher(this->publisherList->get(idx)))
        {
            Publisher publisher = this->getCurrentPublisher();
            ui->publisher_id->setText(QString::number(publisher.getId()));
            ui->publisher_name->setText(publisher.getName());
            ui->publisher_created_at->setDate(publisher.getCreatedAt());
            ui->publisher_updated_at->setDate(publisher.getDeletedAt());
        }

    }
}

void ManagePublisher::on_btn_add_clicked()
{
    QMessageBox *msgBox = new QMessageBox(0);
    msgBox->setWindowTitle(QString::fromUtf8("Thông báo"));
    msgBox->setText(QString::fromUtf8("Bạn có muốn cập nhật?"));
    msgBox->setInformativeText(QString::fromUtf8("Vui lòng kiểm tra lại chính xác thông tin trước khi cập nhật!"));

    if (msgBox->exec() == QMessageBox::Ok)
    {
        QString name = ui->publisher_name->text();
        QDate createdAt = ui->publisher_created_at->date();
        QDate updatedAt = ui->publisher_updated_at->date();

        if (name.size() > 0) {
            PublisherService* publisherService = PublisherService::initPublisherService();
            Publisher publisher(name, createdAt, updatedAt);

            if (publisherService->savePublisher(publisher))
            {

                QMessageBox *successBox = new QMessageBox(0);
                successBox->setWindowTitle(QString::fromUtf8("Thông báo"));
                successBox->setText(QString::fromUtf8("Thêm thành công"));
                successBox->exec();
                on_pushButton_clicked();
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
}

void ManagePublisher::on_pushButton_clicked()
{
    this->currentPublisher = Publisher();
    this->resetIndexRow();
    ui->publisher_id->setText("");
    ui->publisher_name->setText("");
    ui->publisher_created_at->setDate(QDate::currentDate());
    ui->publisher_updated_at->setDate(QDate::currentDate());
}

void ManagePublisher::on_btn_delete_clicked()
{
    Publisher publisher = this->currentPublisher;

    QMessageBox *msgBox = new QMessageBox(0);
    msgBox->setWindowTitle(QString::fromUtf8("Thông báo"));
    msgBox->setText(QString::fromUtf8("Bạn có muốn xóa?"));
    msgBox->setInformativeText(QString::fromUtf8("Vui lòng kiểm tra lại chính xác thông tin trước khi xóa!"));
    if (msgBox->exec() == QMessageBox::Ok)
    {
        if (publisher.getId() >= 0)
        {
            PublisherService* publisherService = PublisherService::initPublisherService();
            if (publisherService->deletePublisherById(publisher.getId()))
            {
                QMessageBox *successBox = new QMessageBox(0);
                successBox->setWindowTitle(QString::fromUtf8("Thông báo"));
                successBox->setText(QString::fromUtf8("Xóa thành công"));
                successBox->exec();
                on_pushButton_clicked();
                on_pushButton_clicked();
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
