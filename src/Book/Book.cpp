#include "Book.h"

Book::Book()
{

}

Book::Book(int book_id, QString title, QString cover_type, float price,
           int total, int available, QDate publication_date, QString size,
           int number_of_pages, int issuing_company_id, int publisher_id,
           int category_id, QDate created_at, QDate updated_at, QDate deleted_at)
{
    this->book_id = book_id;
    this->title = title;
    this->cover_type = cover_type;
    this->price = price;
    this->total = total;
    this->available = available;
    this->publication_date = publication_date;
    this->size = size;
    this->number_of_pages = number_of_pages;
    this->issuing_company_id = issuing_company_id;
    this->publisher_id = publisher_id;
    this->category_id = category_id;
    this->created_at = created_at;
    this->updated_at = updated_at;
    this->deleted_at = deleted_at;
}

Book::~Book()
{

}

int Book::getId() const
{
    return this->book_id;
}

QString Book::getTitle() const
{
    return this->title;
}

void Book::setTitle(const QString title)
{
    this->title = title;
}

QString Book::getCoverType() const
{
    return this->cover_type;
}

QString Book::setCoverType(const QString cover_type)
{
    this->cover_type = cover_type;
}

float Book::getPrice() const
{
    return this->price;
}

float Book::setPrice(const float price)
{
    return this->price = price;
}

int Book::getTotal() const
{
    return this->total;
}

int Book::setTotal(const int total)
{
    this->total = total;
}

int Book::getAvailable() const
{
    this->available;
}

int Book::setAvailable(const int available)
{
    this->available = available;
}

QDate Book::getPublicationDate()
{
    return this->publication_date;
}

QDate Book::setPublicationDate(const QDate date)
{
    this->publication_date = date;
}

QString Book::getSize() const
{
    return this->size;
}

QString Book::setSize(const QString size)
{
    this->size = size;
}

int Book::getNumberOfPages()
{
    return this->number_of_pages;
}

int Book::setNumberOfPages(const int num)
{
    if (num < 0)
    {
        throw "Vui lòng nhập số nguyên không âm!";
    }
    this->number_of_pages = num;
}

QDate Book::getCreatedAt() const
{
    return this->created_at;
}

QDate Book::getUpdatedAt() const
{
    return this->updated_at;
}

void Book::setUpdatedAt(const QDate date)
{
    this->updated_at = date;
}

QDate Book::getDeletedAt() const
{
    return this->deleted_at;
}

Category* Book::getCategory()
{
    return this->category;
}

Category* Book::setCategory(Category* category)
{
    this->category = category;
}

IssuingCompany* Book::getIssuingCompany()
{
    return this->issuingCompany;
}

IssuingCompany* Book::setIssuingCompany(IssuingCompany* issuingCompany)
{
    this->issuingCompany = issuingCompany;
}

Publisher* Book::getPublisher()
{
    return this->publisher;
}

Publisher* Book::setPublisher(Publisher* publisher)
{
    this->publisher = publisher;
}

//Listt<Author*>* Book::getAuthors()
//{
//    return this->authors;
//}

bool Book::addAuthor(Author* author)
{
    this->authors->add(author);
}

bool Book::operator == (const Book& book) const
{
    return (this->getId() == book.getId());
}
