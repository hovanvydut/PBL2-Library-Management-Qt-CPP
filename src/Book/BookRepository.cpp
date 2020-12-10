#include "BookRepository.h"

BookRepository* BookRepository::_bookRepository = nullptr;

BookRepository::BookRepository()
{
    this->query = DatabaseConnection::initDatabaseConnection()->getQuery();
}

BookRepository::~BookRepository()
{

}

BookRepository* BookRepository::initBookRepository()
{
    if (_bookRepository == nullptr)
    {
        _bookRepository = new BookRepository();
    }

    return _bookRepository;
}

/*
Book BookRepository::parse(QSqlQuery *)
{
    int book_id = query->value(0).toInt();
    QString title = query->value(1).toString();
    QString cover_type = query->value(2).toString();
    float price = query->value(3).toFloat();
    int total = query->value(4).toInt();
    int available = query->value(5).toInt();
    QDate publication_date = query->value(6).toDate();
    QString size = query->value(7).toString();
    int number_of_pages = query->value(8).toInt();
    QDate created_at = query->value(12).toDate();
    QDate updated_at = query->value(13).toDate();
    QDate deleted_at = query->value(14).toDate();

    int publisher_id = query->value(10).toInt();
    int issuing_company_id = query->value(9).toInt();
    int category_id = query->value(11).toInt();

    // Quan he nhieu nhieu

    Book book(id, name, created_at, updated_at, deleted_at);

    if (publisher_id)
    {
        QString name = query->value(16).toString();
        QDate created_at = query->value(17).toDate();
        QDate updated_at = query->value(18).toDate();
        QDate deleted_at = query->value(19).toDate();
        Publisher();
    }

    if (category_id)
    {
        QString name = query->value(21).toString();
        QDate created_at = query->value(22).toDate();
        QDate updated_at = query->value(23).toDate();
        QDate deleted_at = query->value(24).toDate();
    }

    if (issuing_company_id)
    {
        QString name = query->value(26).toString();
        QDate created_at = query->value(27).toDate();
        QDate updated_at = query->value(28).toDate();
        QDate deleted_at = query->value(29).toDate();
    }

    return book;
}

Listt<Book>* BookRepository::findAll()
{
    Listt<Book>* list = new LinkedListt<Book>();

    // default query conditions
    int limit = 7;
    int offsetId = 5;

    this->query->prepare(
                "SELECT TOP (:limit) books.*, publishers.*, categories.*, issuing_company.*, authors.*"
                "FROM books LEFT OUTER JOIN publishers ON publishers.publisher_id = books.publisher_id"
                "LEFT OUTER JOIN categories ON categories.categories_id = books.category_id"
                "LEFT OUTER JOIN issuing_company ON issuing_company.issuing_company_id = books.issuing_company_id"
                "LEFT OUTER JOIN author_books ON author_books.book_id = books.book_id"
                "LEFT OUTER JOIN authors ON authors.author_id = author_books.author_id"
                "WHERE books.book_id > (:offsetId)"
                );
    this->query->bindValue(":limit", limit);
    this->query->bindValue(":offsetId", offsetId);

    this->query->exec();
    while(this->query->next())
    {
        list->add(this->parse(this->query));
    }

    return list;
}
*/

Book BookRepository::parse(QSqlQuery *)
{
    int book_id = query->value(0).toInt();
    QString title = query->value(1).toString();
    QString cover_type = query->value(2).toString();
    float price = query->value(3).toFloat();
    int total = query->value(4).toInt();
    int available = query->value(5).toInt();
    QDate publication_date = query->value(6).toDate();
    QString size = query->value(7).toString();
    int number_of_pages = query->value(8).toInt();
    int issuing_company_id = query->value(9).toInt();
    int publisher_id = query->value(10).toInt();
    int category_id = query->value(11).toInt();
    QDate created_at = query->value(12).toDate();
    QDate updated_at = query->value(13).toDate();
    QDate deleted_at = query->value(14).toDate();

    return Book(book_id, title, cover_type, price, total, available, publication_date, size
                , number_of_pages, issuing_company_id, publisher_id, category_id,
                created_at, updated_at, deleted_at);
}

Listt<Book>* BookRepository::findAll()
{
    Listt<Book>* list = new LinkedListt<Book>();

    // default query conditions
    int limit = 7;
    int offsetId = 0;

    this->query->prepare(
                "SELECT TOP (:limit) book_id, title, cover_type, price, total, available, publication_date, size, number_of_pages, issuing_company_id, publisher_id, category_id, created_at, updated_at, deleted_at "
                "FROM books WHERE book_id > (:offsetId)"
                );
    this->query->bindValue(":limit", limit);
    this->query->bindValue(":offsetId", offsetId);

    this->query->exec();
    while(this->query->next())
    {
        list->add(this->parse(this->query));
    }

    return list;
}

Book BookRepository::findById(int id)
{
    this->query->prepare(
                "SELECT book_id, title, cover_type, price, total, available, publication_date, size, number_of_pages, issuing_company_id, publisher_id, category_id, created_at, updated_at, deleted_at "
                "FROM books WHERE book_id = (:id)"
                );
    this->query->bindValue(":id", id);
    this->query->exec();
    this->query->next();
    return this->parse(this->query);
}

Listt<Book>* BookRepository::findByBookTitle(QString title)
{
    Listt<Book>* list = new LinkedListt<Book>();

    QString queryStatement = "SELECT book_id, title, cover_type, price, total, available, publication_date, size, number_of_pages, issuing_company_id, publisher_id, category_id, created_at, updated_at, deleted_at FROM books WHERE UPPER(title) LIKE UPPER('%" + title + "%')";
    this->query->prepare(queryStatement);
    this->query->bindValue(":title", title);

    this->query->exec();
    while(this->query->next())
    {
        list->add(this->parse(this->query));
    }

    return list;
}

