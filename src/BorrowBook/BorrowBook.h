#ifndef BORROWBOOK_H
#define BORROWBOOK_H

#include <QDate>
#include <QString>
#include "src/Book/Book.h"
#pragma once
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
    int user_id;
public:
    BorrowBook();
    BorrowBook(int, QDate, int, Book, int, int, QDate);
    BorrowBook(int, int, Book, int, int, int);
    ~BorrowBook();

    QDate getBorrowedAt();
    int getQuantity();
    Book getBook();
    int getNumOfDay();
    int getDepositMoney();
    QDate getUpdatedAt();
    int getId();
    int getUserId();
    bool operator == (const BorrowBook&) const;
};

#endif // BORROWBOOK_H
