#ifndef MANAGE_AUTHOR_H
#define MANAGE_AUTHOR_H

#include <QDialog>
#include <QStandardItemModel>
#include <QAbstractItemView>
#include <QMessageBox>
#include "src/Author/AuthorService.h"

namespace Ui {
class Manage_Author;
}

class Manage_Author : public QDialog
{
    Q_OBJECT
    Listt<Author> *authorList;
    int indexRow = -1;
    Author currentAuthor;

public:
    explicit Manage_Author(QWidget *parent = 0);
    ~Manage_Author();

    int getIndexRow();
    bool setIndexRow(int idx);
    void resetIndexRow();

    Author getCurrentAuthor();
    bool setCurrentAuthor(Author author);

private slots:
    void on_btn_search_clicked();

    void on_table_author_doubleClicked(const QModelIndex &index);

    void on_btn_add_clicked();

    void on_btn_update_clicked();

    void on_btn_delete_clicked();

    void on_btn_reset_clicked();

private:
    Ui::Manage_Author *ui;
};

#endif // MANAGE_AUTHOR_H
