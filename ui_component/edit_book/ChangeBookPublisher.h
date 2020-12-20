#ifndef CHANGEBOOKPUBLISHER_H
#define CHANGEBOOKPUBLISHER_H

#include <QDialog>

namespace Ui {
class ChangeBookPublisher;
}

class ChangeBookPublisher : public QDialog
{
    Q_OBJECT

public:
    explicit ChangeBookPublisher(QWidget *parent = 0);
    ~ChangeBookPublisher();

private:
    Ui::ChangeBookPublisher *ui;
};

#endif // CHANGEBOOKPUBLISHER_H
