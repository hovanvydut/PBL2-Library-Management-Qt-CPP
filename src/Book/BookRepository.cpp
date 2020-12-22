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

Listt<Book>* BookRepository::findAll()
{
    Listt<Book>* list = new LinkedListt<Book>();

    // default query conditions
    int limit = 100;
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
                "FROM books WHERE book_id = (:id) and deleted_at IS NULL"
                );
    this->query->bindValue(":id", id);
    this->query->exec();
    this->query->next();
    return this->parse(this->query);
}

Listt<Book>* BookRepository::findByBookTitle(QString title)
{
    Listt<Book>* list = new LinkedListt<Book>();

    QString queryStatement = "SELECT book_id, title, cover_type, price, total, available, publication_date, size, number_of_pages, issuing_company_id, publisher_id, category_id, created_at, updated_at, deleted_at FROM books WHERE UPPER(title) LIKE UPPER('%" + title + "%') and deleted_at IS NULL";
    this->query->prepare(queryStatement);
    this->query->bindValue(":title", title);

    this->query->exec();
    while(this->query->next())
    {
        list->add(this->parse(this->query));
    }

    return list;
}

Listt<Book>* BookRepository::findByBookTitle2(QString title)
{
    Listt<Book>* list = new LinkedListt<Book>();
    this->query->prepare("SELECT B.book_id, B.title, B.cover_type, B.price, B.total, B.available, B.publication_date, B.size, B.number_of_pages, "
            "B.issuing_company_id, B.publisher_id, B.category_id, B.created_at, B.updated_at, B.deleted_at,"
            "P.publisher_id, P.name, P.created_at, P.updated_at,P.deleted_at,"
            "I.issuing_company_id, I.name, I.created_at, I.updated_at, I.deleted_at,"
            "C.categories_id, C.name, C.created_at, C.updated_at, C.deleted_at "
        "FROM dbo.books AS B "
        "LEFT OUTER JOIN publishers AS P ON P.publisher_id = B.publisher_id "
        "LEFT OUTER JOIN issuing_company AS I ON I.issuing_company_id = B.issuing_company_id "
        "LEFT OUTER JOIN categories AS C ON C.categories_id = B.category_id "
        "WHERE UPPER(B.title) LIKE UPPER('%" + title + "%') and B.deleted_at IS NULL"
                         );
    this->query->bindValue(":title", title);

    this->query->exec();
    while(this->query->next())
    {
        list->add(this->parse2(this->query));
    }

    // Query authors of book

    AuthorRepository *authorRepo = AuthorRepository::initAuthorRepository();

    for (int i = 0; i < list->getSize(); i++) {    
        this->query->prepare("SELECT A.author_id, A.name, A.created_at, A.updated_at, A.deleted_at"
                             " FROM dbo.author_books AS AB"
                             " LEFT OUTER JOIN dbo.authors AS A ON A.author_id = AB.author_id"
                             " WHERE AB.book_id = " + QString::number(list->get(i).getId())
        );
        this->query->exec();
        while (this->query->next()) {
            Author author = authorRepo->parse(this->query);
            list->get(i).addAuthor(author);
        }
    }

    return list;
}

bool BookRepository::updateBook(Book book)
{
    if (book.getId() >= 0) {
        QString title = book.getTitle();
        QString coverType = book.getCoverType();
        QString price = QString::number(book.getPrice());
        QString total = QString::number(book.getTotal());
        QString available = QString::number(book.getAvailable());
        QString publicationDate = book.getPublicationDate().toString(Qt::ISODate);
        QString size = book.getSize();
        QString number_of_pages = QString::number(book.getNumberOfPages());
        QString issuing_company_id = QString::number(book.getIssuingCompanyId());
        QString publisher_id = QString::number(book.getPublisherId());
        QString category_id = QString::number(book.getCategoryId());
        QString created_at = book.getCreatedAt().toString(Qt::ISODate);
        QString updated_at = book.getUpdatedAt().toString(Qt::ISODate);

        QString deleted_at = "NULL";
        if (!book.getDeletedAt().isNull()) {
            deleted_at = "'" + book.getDeletedAt().toString(Qt::ISODate) + "'";
        }
        QString id = QString::number(book.getId());

        qDebug() << title;

        this->query->prepare("UPDATE books"
                             " SET title = '" + title +
                             "', cover_type = '" + coverType +
                             "', price = " + price +
                             " , total = '" + total +
                             "', available = '" + available +
                             "', publication_date = '" + publicationDate +
                             "', size = '" + size +
                             "', number_of_pages = " + number_of_pages +
                             " , issuing_company_id = " + issuing_company_id +
                             " , publisher_id = " + publisher_id +
                             " , category_id = " + category_id +
                             " , created_at = '" + created_at +
                             "', updated_at = '" + updated_at +
                             "', deleted_at = " + deleted_at +
                             " WHERE book_id = " + id);
        this->query->exec();

        this->query->prepare("DELETE FROM author_books WHERE book_id = " + QString::number(book.getId()));
        this->query->exec();

        Listt<Author>* authorList = book.getAuthors();
        QString txt = "";
        for (int i = 0; i < authorList->getSize(); i++) {
            txt += "(" + QString::number(authorList->get(i).getId()) + ", "
                    + QString::number(book.getId()) + "),";
        }
        if (txt.size() > 0) {
            txt.remove(txt.size()-1, 1);
        }
        this->query->prepare("INSERT INTO author_books(author_id, book_id) "
                             " VALUES " + txt);
        this->query->exec();

        return true;
    }
    return false;
}

Book BookRepository::parse(QSqlQuery *query)
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

Book BookRepository::parse2(QSqlQuery *) {
    Book book = this->parse(query);

    {
        int publisher_id = query->value(15).toInt();
        QString name = query->value(16).toString();
        QDate created_at = query->value(17).toDate();
        QDate updated_at = query->value(18).toDate();
        QDate deleted_at = query->value(19).toDate();
        Publisher* publisher = new Publisher(publisher_id, name, created_at, updated_at,deleted_at);
        book.setPublisher(publisher);
    }

    {
        int id = query->value(20).toInt();
        QString name = query->value(21).toString();
        QDate created_at = query->value(22).toDate();
        QDate updated_at = query->value(23).toDate();
        QDate deleted_at = query->value(24).toDate();
        IssuingCompany *company = new IssuingCompany(id, name, created_at, updated_at, deleted_at);
        book.setIssuingCompany(company);
    }

    {
        int id = query->value(25).toInt();
        QString name = query->value(26).toString();
        QDate created_at = query->value(27).toDate();
        QDate updated_at = query->value(28).toDate();
        QDate deleted_at = query->value(29).toDate();
        Category *category = new Category(id, name, created_at, updated_at, deleted_at);
        book.setCategory(category);
    }

    return book;
}
