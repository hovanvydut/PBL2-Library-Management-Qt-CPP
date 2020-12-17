USE LibraryManagement
CREATE TABLE borrow_books(
	borrow_book_id INT IDENTITY(1, 1) PRIMARY KEY,

	user_id INT NOT NULL FOREIGN KEY REFERENCES users(user_id) ON DELETE CASCADE,
	book_id INT NOT NULL FOREIGN KEY REFERENCES books(book_id) ON DELETE CASCADE,

	quantity INT NOT NULL check(quantity > 0),
	borrowed_at DATETIME DEFAULT GETDATE(), 
	numberOfDay INT NOT NULL check(numberOfDay > 0),
	deposit_money INT check(deposit_money >= 0) DEFAULT 0,
	created_at DATETIME DEFAULT GETDATE(),
	updated_at DATETIME,
	deleted_at DATETIME,
)

