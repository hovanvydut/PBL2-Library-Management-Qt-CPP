#ifndef MANAGEISSUINGCOMPANY_H
#define MANAGEISSUINGCOMPANY_H

#include <QDialog>
#include "src/IssuingCompany/IssuingCompanyService.h"
#include <QStandardItemModel>
#include <QAbstractItemView>
#include <QMessageBox>
namespace Ui {
class ManageIssuingCompany;
}

class ManageIssuingCompany : public QDialog
{
    Q_OBJECT
    Listt<IssuingCompany> *issuingCompanyList;
    int indexRow = -1;
    IssuingCompany currentIssuingCompany;

public:
    explicit ManageIssuingCompany(QWidget *parent = 0);
    ~ManageIssuingCompany();

    int getIndexRow();
    bool setIndexRow(int idx);
    void resetIndexRow();

    IssuingCompany getCurrentIssuingCompany();
    bool setCurrentIssuingCompany(IssuingCompany issuingCompany);

private slots:
    void on_btn_search_2_clicked();

    void on_table_issuing_company_doubleClicked(const QModelIndex &index);

    void on_btn_add_2_clicked();

    void on_btn_update_2_clicked();

    void on_btn_delete_2_clicked();

    void on_btn_reset_2_clicked();

private:
    Ui::ManageIssuingCompany *ui;
};

#endif // MANAGEISSUINGCOMPANY_H
