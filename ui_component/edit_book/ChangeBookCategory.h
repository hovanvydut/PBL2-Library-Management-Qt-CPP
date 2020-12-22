#ifndef CHANGEBOOKCATEGORY_H
#define CHANGEBOOKCATEGORY_H

#include <QDialog>
#include "utils/ListPackage/LinkedListt/LinkedListt.h"
#include "src/Category/CategoryService.h"
#include <QStandardItemModel>

namespace Ui {
class ChangeBookCategory;
}

class ChangeBookCategory : public QDialog
{
    Q_OBJECT
    Category category;
    Listt<Category> *categoryList = nullptr;
    int indexRow = -1;

public:
    explicit ChangeBookCategory(QWidget *parent = 0);
    ~ChangeBookCategory();

    Category getCategory();
    void setCategory(Category category);
    int getIndexRow();
    void setIndexRow(int idx);

private slots:
    void on_btn_search_clicked();

    void on_table_category_doubleClicked(const QModelIndex &index);

    void on_btn_update_clicked();

private:
    Ui::ChangeBookCategory *ui;
};

#endif // CHANGEBOOKCATEGORY_H
