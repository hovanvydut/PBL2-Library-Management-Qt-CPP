#include "ChangeBookPublisher.h"
#include "ui_changebookpublisher.h"

ChangeBookPublisher::ChangeBookPublisher(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::ChangeBookPublisher)
{
    ui->setupUi(this);
}

ChangeBookPublisher::~ChangeBookPublisher()
{
    delete ui;
}
