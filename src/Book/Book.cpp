#include "Book.h"
#include "src/Author/Author.h"

Book::Book()
{
    this->book_id = -1;
    this->authors = new LinkedListt<Author>();
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
    this->authors = new LinkedListt<Author>();
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

QString Book::setTitle(const QString title)
{
    QString oldValue = this->title;
    this->title = title;
    return oldValue;
}

QString Book::getCoverType() const
{
    return this->cover_type;
}

QString Book::setCoverType(const QString cover_type)
{
    QString oldValue = this->cover_type;
    this->cover_type = cover_type;
    return oldValue;
}

float Book::getPrice() const
{
    return this->price;
}

float Book::setPrice(const float price)
{
    float oldValue = this->price;
    this->price = price;
    return oldValue;
}

int Book::getTotal() const
{
    return this->total;
}

int Book::setTotal(const int total)
{
    int oldValue = this->total;
    this->total = total;
    return oldValue;
}

int Book::getAvailable() const
{
    return this->available;
}

int Book::setAvailable(const int available)
{
    int oldValue = this->available;
    this->available = available;
    return oldValue;
}

QDate Book::getPublicationDate()
{
    return this->publication_date;
}

QDate Book::setPublicationDate(const QDate date)
{
    QDate oldValue = this->publication_date;
    this->publication_date = date;
    return oldValue;
}

QString Book::getSize() const
{
    return this->size;
}

QString Book::setSize(const QString size)
{
    QString oldValue = this->size;
    this->size = size;
    return oldValue;
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
    int oldValue = this->number_of_pages;
    this->number_of_pages = num;
    return oldValue;
}

QDate Book::getCreatedAt() const
{
    return this->created_at;
}

QDate Book::getUpdatedAt() const
{
    return this->updated_at;
}

QDate Book::setUpdatedAt(const QDate date)
{
    QDate oldValue = this->updated_at;
    this->updated_at = date;
    return oldValue;
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
    Category* oldValue = this->category;
    this->category = category;
    this->category_id = category->getId();
    return oldValue;
}

IssuingCompany* Book::getIssuingCompany()
{
    return this->issuingCompany;
}

IssuingCompany* Book::setIssuingCompany(IssuingCompany* issuingCompany)
{
    IssuingCompany* oldValue = this->issuingCompany;
    this->issuingCompany = issuingCompany;
    this->issuing_company_id = issuingCompany->getId();
    return oldValue;
}

Publisher* Book::getPublisher()
{
    return this->publisher;
}

Publisher* Book::setPublisher(Publisher* publisher)
{
    Publisher* oldValue = this->publisher;
    this->publisher = publisher;
    this->publisher_id = publisher->getId();
    return oldValue;
}

Listt<Author>* Book::getAuthors()
{
    return this->authors;
}

bool Book::addAuthor(Author author)
{
    this->authors->add(author);
}

void Book::setAnotherAuthorList(Listt<Author>* list)
{
    this->authors->clear();
    this->authors = list;
}

bool Book::operator == (const Book& book) const
{
    return (this->getId() == book.getId());
}

int Book::getIssuingCompanyId()
{
    return this->issuing_company_id;
}

int Book::setIssuingCompanyId(int id)
{
    int oldValue = this->issuing_company_id;
    this->issuing_company_id = id;
    return oldValue;
}

int Book::getPublisherId()
{
    return this->publisher_id;
}

int Book::setPublisherId(int id)
{
    int oldValue = this->publisher_id;
    this->publisher_id = id;
    return oldValue;
}

int Book::getCategoryId()
{
    return this->category_id;
}

int Book::setCategoryId(int id)
{
    int oldValue = this->category_id;
    this->category_id = id;
    return oldValue;
}
