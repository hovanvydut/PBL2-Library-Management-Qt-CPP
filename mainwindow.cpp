#include "mainwindow.h"
#include "ui_mainwindow.h"
#include "src/Publisher/PublisherService.h"
#include "utils/ListPackage/Listt/Listt.h"
#include <QStandardItem>
#include <QDebug>
#include "src/Category/CategoryService.h"

MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow)
{
    ui->setupUi(this);
}

MainWindow::~MainWindow()
{
    delete ui;
}


void MainWindow::on_pushButton_clicked()
{
    try {
        PublisherService* publisherService = PublisherService::initPublisherService();
        Listt<Publisher>* publisherList = publisherService->findAll();

        QStandardItemModel *model = new QStandardItemModel();
        QStringList horizontalHeader;
        horizontalHeader.append("ID");
        horizontalHeader.append(QString::fromUtf8("Tên tác giả"));
        model->setHorizontalHeaderLabels(horizontalHeader);
        ui->tableView->setModel(model);

        for (int i = 0; i < publisherList->getSize(); i++) {
            Publisher publisher = publisherList->get(i);
            QStandardItem *idCol = new QStandardItem(publisher.getId());
            QStandardItem *nameCol = new QStandardItem(publisher.getName());

            model->appendRow( QList<QStandardItem*>() << idCol << nameCol);
        }
    } catch(const char* msg) {
        // show dialog instead console log
        qDebug() << msg;
    }
}

void MainWindow::on_pushButton_2_clicked()
{
    qDebug() << "I'm here!";
    try {
        CategoryService* categoryService = CategoryService::initCategoryService();
        Listt<Category>* categoryList = categoryService->findAll();

        QStandardItemModel *model = new QStandardItemModel();
        QStringList horizontalHeader;
        horizontalHeader.append("ID");
        horizontalHeader.append(QString::fromUtf8("Category name"));
        model->setHorizontalHeaderLabels(horizontalHeader);
        ui->tableView->setModel(model);

        for (int i = 0; i < categoryList->getSize(); i++) {
            Category category = categoryList->get(i);
            QStandardItem *idCol = new QStandardItem(category.getId());
            QStandardItem *nameCol = new QStandardItem(category.getName());

            model->appendRow( QList<QStandardItem*>() << idCol << nameCol);
        }
    } catch(const char* msg) {
        // show dialog instead console log
        qDebug() << msg;
    }
}
