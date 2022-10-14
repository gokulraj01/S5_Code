CLEAR SCR

-- Drop old tables
DROP TABLE branch CASCADE CONSTRAINTS;
DROP TABLE customer CASCADE CONSTRAINTS;
DROP TABLE loan CASCADE CONSTRAINTS;
DROP TABLE borrower CASCADE CONSTRAINTS;
DROP TABLE account CASCADE CONSTRAINTS;
DROP TABLE depositor CASCADE CONSTRAINTS;
DROP TABLE employee CASCADE CONSTRAINTS;

-- PURGE recyclebin
PURGE RECYCLEBIN;

-- Banking Database
CREATE TABLE branch(
	branch_name VARCHAR(20) PRIMARY KEY,
	branch_city VARCHAR(20),
	assets VARCHAR(20)
);

CREATE TABLE customer(
	customer_name VARCHAR(20) PRIMARY KEY,
	customer_street VARCHAR(20),
	customer_city VARCHAR(20)
);

CREATE TABLE loan(
	loan_number INTEGER PRIMARY KEY,
	branch_name VARCHAR(20),
	loan_amount INTEGER,
	FOREIGN KEY (branch_name) REFERENCES branch(branch_name)
);

CREATE TABLE borrower(
	customer_name VARCHAR(20) PRIMARY KEY,
	loan_number INTEGER,
	FOREIGN KEY (customer_name) REFERENCES customer(customer_name),
	FOREIGN KEY (loan_number) REFERENCES loan(loan_number)
);

CREATE TABLE account(
	account_number INTEGER PRIMARY KEY,
	branch_name VARCHAR(20),
	balance INTEGER,
	FOREIGN KEY (branch_name) REFERENCES branch(branch_name)
);

CREATE TABLE depositor(
	customer_name VARCHAR(20),
	account_number INTEGER,
	FOREIGN KEY (customer_name) REFERENCES customer(customer_name),
	FOREIGN KEY (account_number) REFERENCES account(account_number)
);

CREATE TABLE employee(
	employee_name VARCHAR(20),
	branch_name VARCHAR(20),
	dob DATE,
	salary INTEGER,
	FOREIGN KEY (branch_name) REFERENCES branch(branch_name),
	PRIMARY KEY (employee_name, branch_name)
);

SELECT * FROM TAB;