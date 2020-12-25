USE LibraryManagement
-- Reset
DELETE FROM borrow_books WHERE 1=1

UPDATE books SET total=5, available=5

-- Testing

INSERT INTO borrow_books(user_id, book_id, quantity, numberOfDay) VALUES (1, 1, 1, 2), (1, 2, 1, 1)

INSERT INTO borrow_books(user_id, book_id, quantity, numberOfDay) VALUES (1, 2, 10, 1)

-- Change id borrow here
- UPDATE borrow_books SET deleted_at = GETDATE() WHERE borrow_book_id = 52

SELECT TOP 10 * FROM books

SELECT TOP 10 * FROM borrow_books

-- Return book

UPDATE borrow_books SET deleted_at = GETDATE() WHERE borrow_book_id = 2