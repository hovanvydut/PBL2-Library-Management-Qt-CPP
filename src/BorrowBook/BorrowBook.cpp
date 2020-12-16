#include "BorrowBook.h"

BorrowBook::BorrowBook()
{

}

BorrowBook::BorrowBook(int id, QDate borrowed_at, int quantity, Book book, int num_of_day, int deposit_money, QDate updated_at){
    this->id = id;
    this->borrowed_at = borrowed_at;
    this->quantity = quantity;
    this->book = book;
    this->num_of_day = num_of_day;
    this->deposit_money = deposit_money;
    this->updated_at = updated_at;
}

QDate BorrowBook::getBorrowedAt(){
    return this->borrowed_at;
}
int BorrowBook::getQuantity(){
    return this->quantity;
}
Book BorrowBook::getBook(){
    return this->book;
}
int BorrowBook::getNumOfDay(){
    return this->num_of_day;
}
int BorrowBook::getDepositMoney(){
    return this->deposit_money;
}
QDate BorrowBook::getUpdatedAt(){
    return this->updated_at;
}
int BorrowBook::getId(){
    return this->id;
}

bool BorrowBook::operator == (const BorrowBook& b) const{
    return this->id == b.id;
}

BorrowBook::~BorrowBook()
{

}

