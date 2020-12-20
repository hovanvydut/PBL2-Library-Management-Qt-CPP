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
	role_id INT FOREIGN KEY REFERENCES roles(role_id) ON DELETE SET NULL ,
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
INSERT INTO roles(code, description) VALUES('superuser', 'Quan li tat ca')
INSERT INTO roles(code, description) VALUES('admin', 'Quan li nhan vien')
INSERT INTO roles(code, description) VALUES('employee', 'Quan li khach hang')
INSERT INTO roles(code, description) VALUES('guest', 'Khach hang')

INSERT INTO users(role_id, fullname) VALUES(1, 'Nguyen Huy Tupng super')
INSERT INTO users(role_id, fullname) VALUES(2, 'Nguyen Huy Tupng admin')
INSERT INTO users(role_id, fullname) VALUES(3, 'Nguyen Huy Tupng employee')
INSERT INTO users(role_id, fullname) VALUES(4, 'Nguyen Huy Tupng guest')
