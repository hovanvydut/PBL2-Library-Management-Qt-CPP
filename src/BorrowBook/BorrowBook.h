#ifndef BORROWBOOK_H
#define BORROWBOOK_H

#include <QDate>
#include <QString>
#include "src/Book/Book.h"
#include "utils/Comparable/Comparable.h"

class BorrowBook: public Comparable<BorrowBook>
{
private:
    QDate borrowed_at;
    int quantity;
    Book book;
    int num_of_day;
    int deposit_money;
    QDate updated_at;
    int id;
public:
    BorrowBook();
    BorrowBook(int, QDate, int, Book, int, int, QDate);
    ~BorrowBook();

    QDate getBorrowedAt();
    int getQuantity();
    Book getBook();
    int getNumOfDay();
    int getDepositMoney();
    QDate getUpdatedAt();
    int getId();
    bool operator == (const BorrowBook&) const;
};

#endif // BORROWBOOK_H
