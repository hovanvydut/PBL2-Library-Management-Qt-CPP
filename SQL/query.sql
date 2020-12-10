USE LibraryManagement

SELECT TOP 7 books.*, publishers.*, categories.*, issuing_company.*, authors.*
FROM books LEFT OUTER JOIN publishers ON publishers.publisher_id = books.publisher_id
LEFT OUTER JOIN categories ON categories.categories_id = books.category_id
LEFT OUTER JOIN issuing_company ON issuing_company.issuing_company_id = books.issuing_company_id
LEFT OUTER JOIN author_books ON author_books.book_id = books.book_id
LEFT OUTER JOIN authors ON authors.author_id = author_books.author_id
WHERE books.book_id > 5

SELECT A.*, B.book_id, title, cover_type, price, total, available, publication_date, size, 
number_of_pages, issuing_company_id, publisher_id, category_id, B.created_at, B.updated_at, 
B.deleted_at
FROM dbo.books AS B
INNER JOIN dbo.author_books ON author_books.book_id = B.book_id
INNER JOIN dbo.authors AS A ON A.author_id = author_books.author_id
WHERE A.name = 'Nguyen Huu Hung'

SELECT * FROM dbo.authors WHERE UPPER(name) LIKE UPPER('nguyen huu hung')