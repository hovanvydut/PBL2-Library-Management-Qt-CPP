USE LibraryManagement

CREATE TRIGGER updateBorrowBook
ON borrow_books 
FOR UPDATE
AS BEGIN
	
	DECLARE @book_id INT,
			@inc INT,
			@available INT,
			@borrow_id INT
	-- get book_id will update
	SELECT @book_id = book_id FROM DELETED
	SELECT @borrow_id = borrow_book_id FROM INSERTED 

	-- get available and num of book will increase
	SET @inc = (SELECT quantity FROM inserted) + (SELECT quantity FROM deleted)
	SELECT @available = available FROM books WHERE book_id = @book_id
	
	-- Check if deleted
	IF (SELECT deleted_at FROM deleted) IS NOT NULL
	BEGIN
		PRINT('Cannot update rows deleted')
		ROLLBACK TRANSACTION
	END
	-- Check if not enough book
	ELSE IF @available + @inc < 0
		BEGIN
			PRINT('Not enogh books')
			ROLLBACK TRANSACTION
		END
	BEGIN
		-- Let update
		-- Firstm update the date updated
		UPDATE borrow_books SET updated_at = GETDATE() WHERE borrow_book_id = @borrow_id
		-- return quantity if delete
		IF (SELECT deleted_at FROM deleted) IS NULL AND (SELECT deleted_at FROM inserted) IS NOT NULL
		BEGIN
			UPDATE books SET available = available + 
			(SELECT quantity FROM inserted)
			WHERE book_id = @book_id
			PRINT('DELETED SUCCESS')
		END
		-- Update available
		ELSE
			UPDATE books SET available = available -
				(SELECT quantity FROM inserted) +
				(SELECT quantity FROM deleted)
			WHERE book_id = @book_id
			PRINT('UPDATE SUCCESS')
	END
	
END

-- DROP TRIGGER updateBorrowBook