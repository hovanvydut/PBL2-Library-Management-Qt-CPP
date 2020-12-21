#ifndef CHANGEBOOKPUBLISHER_H
#define CHANGEBOOKPUBLISHER_H

#include <QDialog>
#include "src/Publisher/PublisherService.h"
#include <QStandardItemModel>
#include <QAbstractItemView>

namespace Ui {
class ChangeBookPublisher;
}

class ChangeBookPublisher : public QDialog
{
    Q_OBJECT
    Publisher publisher;
    Listt<Publisher> *publisherList = nullptr;
    int indexRow = -1;

public:
    explicit ChangeBookPublisher(QWidget *parent = 0);
    ~ChangeBookPublisher();

    Publisher getPublisher();
    void setPublisher(Publisher publisher);
    int getIndexRow();
    void setIndexRow(int idx);

private slots:
    void on_btn_search_clicked();

    void on_table_publisher_doubleClicked(const QModelIndex &index);

    void on_btn_update_clicked();

private:
    Ui::ChangeBookPublisher *ui;
};

#endif // CHANGEBOOKPUBLISHER_H
