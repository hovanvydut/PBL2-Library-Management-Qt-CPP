#ifndef CHANGEBOOKISSUINGCOMPANY_H
#define CHANGEBOOKISSUINGCOMPANY_H

#include <QDialog>
#include "src/IssuingCompany/IssuingCompanyService.h"
#include <QStandardItem>

namespace Ui {
class ChangeBookIssuingCompany;
}

class ChangeBookIssuingCompany : public QDialog
{
    Q_OBJECT
    IssuingCompany issuingCompany;
    Listt<IssuingCompany> *issuingCompanyList = nullptr;
    int indexRow = -1;

public:
    explicit ChangeBookIssuingCompany(QWidget *parent = 0);
    ~ChangeBookIssuingCompany();

    IssuingCompany getIssuingCompany();
    void setIssuingCompany(IssuingCompany issuingCompany);
    int getIndexRow();
    void setIndexRow(int idx);

private slots:
    void on_btn_search_clicked();

    void on_table_issuing_company_doubleClicked(const QModelIndex &index);

    void on_btn_update_clicked();

private:
    Ui::ChangeBookIssuingCompany *ui;
};

#endif // CHANGEBOOKISSUINGCOMPANY_H
