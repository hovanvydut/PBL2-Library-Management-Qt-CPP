USE LibraryManagement
-- Trigger insert
CREATE TRIGGER insertBorrowBook 
ON borrow_books
FOR INSERT AS 
BEGIN

-- inserted: chua cai se insert
	--Declare
	DECLARE @expectInsert INT,
			@validInsert INT	

	-- Count valid
	SELECT @validInsert = COUNT(borrow_book_id) 
	FROM books
	JOIN inserted ON books.book_id = inserted.book_id AND books.available >= inserted.quantity;

	SELECT @expectInsert = COUNT(borrow_book_id)
	FROM INSERTED

	-- Check if valid
	IF @expectInsert != @validInsert
	BEGIN
		PRINT('Not enoungh book to borrow')
		ROLLBACK TRANSACTION
	END
	-- Start insert
	UPDATE books
	SET available = available - (
		SELECT quantity
		FROM inserted
		WHERE book_id = books.book_id
	)
	FROM books
	JOIN inserted ON books.book_id = inserted.book_id;
	-- debug

END
-- Reset
-- DROP TRIGGER insertBorrowBook
