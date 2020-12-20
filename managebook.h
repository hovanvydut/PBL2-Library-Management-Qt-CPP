#ifndef MANAGEBOOK_H
#define MANAGEBOOK_H

#include <QDialog>
#include "utils/ListPackage/Listt/Listt.h"
#include "src/Book/Book.h"
#include <QModelIndex>
#include <QAbstractItemView>


namespace Ui {
class managebook;
}

class managebook : public QDialog
{
    Q_OBJECT
    Listt<Book> *bookList;
    int indexRow = 0;

public:
    explicit managebook(QWidget *parent = 0);
    ~managebook();
    void setIndexRow(int);
    int getIndexRow();

private slots:

    void on_btn_search_clicked();

    void on_table_book_doubleClicked(const QModelIndex &index);

    void on_btn_change__book_publisher_clicked();

    void on_btn_reset_book_clicked();

private:
    Ui::managebook *ui;
};

#endif // MANAGEBOOK_H
