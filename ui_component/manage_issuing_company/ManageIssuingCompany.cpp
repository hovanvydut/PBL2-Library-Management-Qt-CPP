#include "ManageIssuingCompany.h"
#include "ui_ManageIssuingCompany.h"

ManageIssuingCompany::ManageIssuingCompany(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::ManageIssuingCompany)
{
    ui->setupUi(this);
    ui->table_issuing_company->setEditTriggers(QAbstractItemView::NoEditTriggers);
    this->issuingCompanyList = new LinkedListt<IssuingCompany>();
}

int ManageIssuingCompany::getIndexRow()
{
    return this->indexRow;
}

bool ManageIssuingCompany::setIndexRow(int idx)
{
    if (idx < 0)
        return false;
    this->indexRow = idx;
    return true;
}

void ManageIssuingCompany::resetIndexRow()
{
    this->indexRow = -1;
}

IssuingCompany ManageIssuingCompany::getCurrentIssuingCompany()
{
    return this->currentIssuingCompany;
}

bool ManageIssuingCompany::setCurrentIssuingCompany(IssuingCompany issuingCompany)
{
    this->currentIssuingCompany = issuingCompany;
    return true;
}

ManageIssuingCompany::~ManageIssuingCompany()
{
    delete ui;
}

void ManageIssuingCompany::on_btn_search_2_clicked()
{
    IssuingCompanyService* issuingCompanyService = IssuingCompanyService::initIssuingCompanyService();

     QString byName = ui->input_search_2->text();

     // Tìm kiếm theo tên sách
     this->issuingCompanyList->clear();

     this->issuingCompanyList = issuingCompanyService->findByName(byName);

     QStandardItemModel *model = new QStandardItemModel();
     QStringList horizontalHeader;
     horizontalHeader.append("Id");
     horizontalHeader.append(QString::fromUtf8("Tên"));
     horizontalHeader.append(QString::fromUtf8("Ngày tạo"));
     horizontalHeader.append(QString::fromUtf8("Cập nhật lần cưới"));
     model->setHorizontalHeaderLabels(horizontalHeader);
     ui->table_issuing_company->setModel(model);

     for (int i = 0; i < this->issuingCompanyList->getSize(); i++) {
         IssuingCompany issuingCompany = this->issuingCompanyList->get(i);
         QStandardItem *idCol = new QStandardItem(QString::number(issuingCompany.getId()));
         QStandardItem *nameCol = new QStandardItem(issuingCompany.getName());
         QStandardItem *createdAtCol = new QStandardItem(issuingCompany.getCreatedAt().toString());
         QStandardItem *updatedAtCol = new QStandardItem(issuingCompany.getUpdatedAt().toString());
         model->appendRow( QList<QStandardItem*>() << idCol << nameCol << createdAtCol << updatedAtCol);
     }
}

void ManageIssuingCompany::on_table_issuing_company_doubleClicked(const QModelIndex &index)
{
    int idx = index.row();

    if (this->setIndexRow(idx))
    {
        if (this->setCurrentIssuingCompany(this->issuingCompanyList->get(idx)))
        {
            IssuingCompany issuingCompany = this->getCurrentIssuingCompany();
            ui->issuing_company_id->setText(QString::number(issuingCompany.getId()));
            ui->issuing_company_name->setText(issuingCompany.getName());
            ui->issuing_company_created_at->setDate(issuingCompany.getCreatedAt());
            ui->issuing_company_updated_at->setDate(issuingCompany.getDeletedAt());
        }

    }
}

void ManageIssuingCompany::on_btn_add_2_clicked()
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
        QString name = ui->issuing_company_name->text();
        QDate createdAt = ui->issuing_company_created_at->date();
        QDate updatedAt = ui->issuing_company_updated_at->date();

        if (name.size() > 0) {
            IssuingCompanyService* issuingCompanyService = IssuingCompanyService::initIssuingCompanyService();
            IssuingCompany issuingCompany(name, createdAt, updatedAt);

            if (issuingCompanyService->saveIssuingCompany(issuingCompany))
            {

                QMessageBox *successBox = new QMessageBox(0);
                successBox->setWindowTitle(QString::fromUtf8("Thông báo"));
                successBox->setText(QString::fromUtf8("Thêm thành công"));
                successBox->exec();
                on_btn_reset_2_clicked();
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

void ManageIssuingCompany::on_btn_update_2_clicked()
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
        if (this->currentIssuingCompany.getId() >= 0)
        {
            int id = this->currentIssuingCompany.getId();

            QString name = ui->issuing_company_name->text();
            QDate createdAt = ui->issuing_company_created_at->date();
            QDate updatedAt = ui->issuing_company_updated_at->date();

            IssuingCompany issuingCompany(id, name, createdAt, updatedAt);

            IssuingCompanyService* issuingCompanyService = IssuingCompanyService::initIssuingCompanyService();

            if (issuingCompanyService->updateIssuingCompany(issuingCompany))
            {
                QMessageBox *successBox = new QMessageBox(0);
                successBox->setWindowTitle(QString::fromUtf8("Thông báo"));
                successBox->setText(QString::fromUtf8("Cập nhật thành công"));
                successBox->exec();
                on_btn_reset_2_clicked();
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

void ManageIssuingCompany::on_btn_delete_2_clicked()
{
    IssuingCompany issuingCompany = this->currentIssuingCompany;

    QMessageBox *msgBox = new QMessageBox(0);
    msgBox->setWindowTitle(QString::fromUtf8("Thông báo"));
    msgBox->setText(QString::fromUtf8("Bạn có muốn xóa?"));
    msgBox->setInformativeText(QString::fromUtf8("Vui lòng kiểm tra lại chính xác thông tin trước khi xóa!"));
    msgBox->setStandardButtons(QMessageBox::Ok | QMessageBox::Cancel);
    msgBox->setDefaultButton(QMessageBox::Ok);
    int ret = msgBox->exec();
    if (ret == QMessageBox::Ok)
    {
        if (issuingCompany.getId() >= 0)
        {
            IssuingCompanyService* issuingCompanyService = IssuingCompanyService::initIssuingCompanyService();
            if (issuingCompanyService->deleteIssuingCompanyById(issuingCompany.getId()))
            {
                QMessageBox *successBox = new QMessageBox(0);
                successBox->setWindowTitle(QString::fromUtf8("Thông báo"));
                successBox->setText(QString::fromUtf8("Xóa thành công"));
                successBox->exec();
                on_btn_reset_2_clicked();
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

void ManageIssuingCompany::on_btn_reset_2_clicked()
{
    this->currentIssuingCompany = IssuingCompany();
    this->resetIndexRow();

    ui->issuing_company_id->setText("");
    ui->issuing_company_name->setText("");
    ui->issuing_company_created_at->setDate(QDate::currentDate());
    ui->issuing_company_updated_at->setDate(QDate::currentDate());
}
