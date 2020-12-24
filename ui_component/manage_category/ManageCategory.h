#ifndef MANAGECATEGORY_H
#define MANAGECATEGORY_H

#include <QDialog>
#include "src/Category/CategoryService.h"
#include <QStandardItemModel>
#include <QAbstractItemView>
#include <QMessageBox>

namespace Ui {
class ManageCategory;
}

class ManageCategory : public QDialog
{
    Q_OBJECT
    Listt<Category> *categoryList;
    int indexRow = -1;
    Category currentCategory;

public:
    explicit ManageCategory(QWidget *parent = 0);
    ~ManageCategory();

    int getIndexRow();
    bool setIndexRow(int idx);
    void resetIndexRow();

    Category getCurrentCategory();
    bool setCurrentCategory(Category category);

private slots:
    void on_btn_search_clicked();

    void on_table_category_doubleClicked(const QModelIndex &index);

    void on_btn_add_clicked();

    void on_btn_update_clicked();

    void on_btn_delete_clicked();

    void on_btn_reset_clicked();

private:
    Ui::ManageCategory *ui;
};

#endif // MANAGECATEGORY_H
