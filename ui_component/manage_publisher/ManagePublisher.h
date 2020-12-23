#ifndef MANAGEPUBLISHER_H
#define MANAGEPUBLISHER_H

#include <QDialog>
#include "src/Publisher/PublisherService.h"
#include <QStandardItemModel>
#include <QAbstractItemView>
#include <QMessageBox>

namespace Ui {
class ManagePublisher;
}

class ManagePublisher : public QDialog
{
    Q_OBJECT
    Listt<Publisher> *publisherList;
    int indexRow = -1;
    Publisher currentPublisher;

public:
    explicit ManagePublisher(QWidget *parent = 0);
    ~ManagePublisher();

    int getIndexRow();
    bool setIndexRow(int idx);
    void resetIndexRow();

    Publisher getCurrentPublisher();
    bool setCurrentPublisher(Publisher publisher);

private slots:
    void on_btn_search_clicked();

    void on_table_publisher_doubleClicked(const QModelIndex &index);

    void on_btn_add_clicked();

    void on_pushButton_clicked();

    void on_btn_delete_clicked();

private:
    Ui::ManagePublisher *ui;
};

#endif // MANAGEPUBLISHER_H
