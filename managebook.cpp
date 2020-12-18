#include "managebook.h"
#include "ui_managebook.h"

managebook::managebook(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::managebook)
{
    ui->setupUi(this);
}

managebook::~managebook()
{
    delete ui;
}
