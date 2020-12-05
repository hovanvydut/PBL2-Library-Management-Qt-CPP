USE LibraryManagement

SELECT TOP 7 books.*, publishers.*, categories.*, issuing_company.*, authors.*
FROM books LEFT OUTER JOIN publishers ON publishers.publisher_id = books.publisher_id
LEFT OUTER JOIN categories ON categories.categories_id = books.category_id
LEFT OUTER JOIN issuing_company ON issuing_company.issuing_company_id = books.issuing_company_id
LEFT OUTER JOIN author_books ON author_books.book_id = books.book_id
LEFT OUTER JOIN authors ON authors.author_id = author_books.author_id
WHERE books.book_id > 5