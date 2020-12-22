USE LibraryManagement

-- Create Table
CREATE TABLE roles (
	role_id INT IDENTITY(1, 1) NOT NULL PRIMARY KEY,
	code VARCHAR(10),
	description NVARCHAR(100),
	priorty TINYINT, 

)

CREATE TABLE users (
	user_id INT IDENTITY(1, 1) NOT NULL PRIMARY KEY,
	role_id INT FOREIGN KEY REFERENCES roles(role_id) ON DELETE SET NULL,
	fullname NVARCHAR(70) NOT NULL,
	birthday DATE,
	gender TINYINT check(gender = 0 OR gender = 1 OR gender = 2),
	email VARCHAR(100),
	phone VARCHAR(11),
	username VARCHAR(20) check(LEN(username) > 5),
	password VARCHAR(32) check(LEN(password) > 10),
	address NVARCHAR(200),
	created_at DATETIME DEFAULT GETDATE(),
	updated_at DATETIME ,
)

-- Seeding data
INSERT INTO roles(code, description, priorty) VALUES('superuser', 'Quản lí chung', 0)
INSERT INTO roles(code, description, priorty) VALUES('admin', 'Quản lí nhân viên và khách hàng', 1)
INSERT INTO roles(code, description, priorty) VALUES('employee', 'Quản lí khách hàng', 2)
INSERT INTO roles(code, description, priorty) VALUES('guest', 'Khách hàng', 3)
-- change role_id to role_id of superuser
INSERT INTO users(fullname, phone, gender, birthday, role_id, username, password) VALUES(N'Quản lí', '0123456789', 0, '01/01/2001', 1, 'superuser', 'd94354ac9cf3024f57409bd74eec6b4c')
