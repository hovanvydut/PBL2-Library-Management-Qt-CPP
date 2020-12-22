#include "ChangeBookIssuingCompany.h"
#include "ui_ChangeBookIssuingCompany.h"

ChangeBookIssuingCompany::ChangeBookIssuingCompany(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::ChangeBookIssuingCompany)
{
    ui->setupUi(this);
    ui->table_issuing_company->setEditTriggers(QAbstractItemView::NoEditTriggers);
}

ChangeBookIssuingCompany::~ChangeBookIssuingCompany()
{
    delete ui;
}

IssuingCompany ChangeBookIssuingCompany::getIssuingCompany()
{
    return this->issuingCompany;
}

void ChangeBookIssuingCompany::setIssuingCompany(IssuingCompany issuingCompany)
{
    this->issuingCompany = issuingCompany;
}

int ChangeBookIssuingCompany::getIndexRow()
{
    return this->indexRow;
}

void ChangeBookIssuingCompany::setIndexRow(int idx)
{
    this->indexRow = idx;
}

void ChangeBookIssuingCompany::on_btn_search_clicked()
{
    QString searchValue = ui->input_search_issuing_company->text();
    IssuingCompanyService *issuingCompanyService = IssuingCompanyService::initIssuingCompanyService();
    this->issuingCompanyList = issuingCompanyService->findByName(searchValue);

    QStandardItemModel *model = new QStandardItemModel();
    QStringList horizontalHeader;
    horizontalHeader.append("Id");
    horizontalHeader.append(QString::fromUtf8("Tên"));
    horizontalHeader.append(QString::fromUtf8("Ngày tạo"));
    horizontalHeader.append(QString::fromUtf8("Cập nhật lần cuối"));
    horizontalHeader.append(QString::fromUtf8("Xóa mềm"));
    model->setHorizontalHeaderLabels(horizontalHeader);
    ui->table_issuing_company->setModel(model);

    for (int i = 0; i < this->issuingCompanyList->getSize(); i++) {
        IssuingCompany issuingCompany = this->issuingCompanyList->get(i);
        QStandardItem *idCol = new QStandardItem(QString::number(issuingCompany.getId()));
        QStandardItem *nameCol = new QStandardItem(issuingCompany.getName());
        QStandardItem *created_at = new QStandardItem(issuingCompany.getCreatedAt().toString("dd.MM.yyyy"));
        QStandardItem *updated_at = new QStandardItem(issuingCompany.getUpdatedAt().toString("dd.MM.yyyy"));
        model->appendRow( QList<QStandardItem*>() << idCol << nameCol << created_at << updated_at);
    }
}

void ChangeBookIssuingCompany::on_table_issuing_company_doubleClicked(const QModelIndex &index)
{
    ui->table_issuing_company->setEditTriggers(QAbstractItemView::NoEditTriggers);
    int idx = index.row();

    if (idx >= 0) {
        IssuingCompany issuingCompany = this->issuingCompanyList->get(idx);

        this->setIssuingCompany(issuingCompany);
        this->setIndexRow(idx);

        ui->current_issuing_company->setText(issuingCompany.getName());
    }
}

void ChangeBookIssuingCompany::on_btn_update_clicked()
{
    this->accept();
}
