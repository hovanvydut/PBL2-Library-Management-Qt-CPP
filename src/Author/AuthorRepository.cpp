#include "AuthorRepository.h"

AuthorRepository* AuthorRepository::_authorRepository = nullptr;

AuthorRepository::AuthorRepository()
{
    this->query = DatabaseConnection::initDatabaseConnection()->getQuery();
}

AuthorRepository::~AuthorRepository()
{

}

AuthorRepository* AuthorRepository::initAuthorRepository()
{
    if (_authorRepository == nullptr)
    {
        _authorRepository = new AuthorRepository();
    }

    return _authorRepository;
}

Author AuthorRepository::parse(QSqlQuery *)
{
    int id = query->value(0).toInt();
    QString name = query->value(1).toString();
    QDate created_at = query->value(2).toDate();
    QDate updated_at = query->value(3).toDate();
    QDate deleted_at = query->value(4).toDate();
    return Author(id, name, created_at, updated_at, deleted_at);
}

Listt<Author>* AuthorRepository::findAll()
{
    Listt<Author>* list = new LinkedListt<Author>();

    // default query conditions
    int limit = 7;
    int offsetId = 5;

    this->query->prepare("SELECT TOP(:limit) author_id, name, created_at, updated_at, deleted_at "
                         "FROM authors WHERE author_id > :offsetId");
    this->query->bindValue(":limit", limit);
    this->query->bindValue(":offsetId", offsetId);

    this->query->exec();
    while(this->query->next())
    {
        list->add(this->parse(this->query));
    }

    return list;
}

Book AuthorRepository::parseBook(QSqlQuery *, int offset)
{
    int book_id = query->value(0 + offset).toInt();
    QString title = query->value(1 + offset).toString();
    QString cover_type = query->value(2 + offset).toString();
    float price = query->value(3 + offset).toFloat();
    int total = query->value(4 + offset).toInt();
    int available = query->value(5 + offset).toInt();
    QDate publication_date = query->value(6 + offset).toDate();
    QString size = query->value(7 + offset).toString();
    int number_of_pages = query->value(8 + offset).toInt();
    int issuing_company_id = query->value(9 + offset).toInt();
    int publisher_id = query->value(10 + offset).toInt();
    int category_id = query->value(11 + offset).toInt();
    QDate created_at = query->value(12 + offset).toDate();
    QDate updated_at = query->value(13 + offset).toDate();
    QDate deleted_at = query->value(14 + offset).toDate();

    return Book(book_id, title, cover_type, price, total, available, publication_date, size
                , number_of_pages, issuing_company_id, publisher_id, category_id,
                created_at, updated_at, deleted_at);
}


Listt<Author>* AuthorRepository::findBooksOfAuthorByAuthorName(QString name)
{
    qDebug() << "AuthorRepository";
    Listt<Author>* listAuthors = new LinkedListt<Author>();

    QString queryStatement = "SELECT A.*, B.book_id, title, cover_type, price, total, available, publication_date, size, "
            "number_of_pages, issuing_company_id, publisher_id, category_id, B.created_at, B.updated_at, "
            "B.deleted_at "
            "FROM dbo.books AS B "
            "INNER JOIN dbo.author_books ON author_books.book_id = B.book_id "
            "INNER JOIN dbo.authors AS A ON A.author_id = author_books.author_id "
            "WHERE UPPER(A.name) LIKE UPPER('%" + name + "%')";
    this->query->prepare(queryStatement);

    this->query->exec();
    while(this->query->next())
    {
        qDebug() << "1";
        Author author = this->parse(this->query);
        qDebug() << "Author: " << author.getName() << ", " << author.getId();
        qDebug() << listAuthors->contains(author);
        if (listAuthors->contains(author))
        {
            qDebug() << "2";
            int idx = listAuthors->indexOf(author);
            if (idx >= 0) {
                listAuthors->get(idx).addBook(parseBook(this->query, 5));
            }
        } else
        {
            qDebug() << "3";
            Book book = parseBook(this->query, 5);
            qDebug() << "3.1";
            author.addBook(book);
            qDebug() << "3.2";
            listAuthors->add(author);
            qDebug() << "3.3";
        }
    }

    for (int i = 0; i < listAuthors->getSize(); i++)
    {
        qDebug() << listAuthors->get(i).getName();
    }

    return listAuthors;
}

