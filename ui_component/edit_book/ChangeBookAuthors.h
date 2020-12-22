#ifndef CHANGEBOOKAUTHORS_H
#define CHANGEBOOKAUTHORS_H

#include <QDialog>
#include "src/Author/AuthorService.h"
#include <QStandardItemModel>

namespace Ui {
class ChangeBookAuthors;
}

class ChangeBookAuthors : public QDialog
{
    Q_OBJECT
    Listt<Author>* currentAuthorList;
    Listt<Author> *allAuthorList = nullptr;
    int indexRow = -1;

public:
    explicit ChangeBookAuthors(QWidget *parent = 0);
    ~ChangeBookAuthors();

    Listt<Author>* getCurrentAuthorList();
    void setCurrentAuthorList(Listt<Author>* list);
    int getIndexRow();
    void setIndexRow(int idx);

private slots:
    void on_btn_search_clicked();

    void on_table_author_doubleClicked(const QModelIndex &index);

    void on_table_current_author_doubleClicked(const QModelIndex &index);

    void on_btn_update_clicked();

private:
    Ui::ChangeBookAuthors *ui;
    QStandardItemModel* currentAuthorModelUi;
};

#endif // CHANGEBOOKAUTHORS_H
