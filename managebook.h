#ifndef MANAGEBOOK_H
#define MANAGEBOOK_H

#include <QDialog>

namespace Ui {
class managebook;
}

class managebook : public QDialog
{
    Q_OBJECT

public:
    explicit managebook(QWidget *parent = 0);
    ~managebook();

private:
    Ui::managebook *ui;
};

#endif // MANAGEBOOK_H
