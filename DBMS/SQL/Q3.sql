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
	branch_name VARCHAR(25) PRIMARY KEY,
	branch_city VARCHAR(25),
	assets INTEGER
);

CREATE TABLE customer(
	customer_name VARCHAR(25) PRIMARY KEY,
	customer_street VARCHAR(25),
	customer_city VARCHAR(25)
);

CREATE TABLE loan(
	loan_number INTEGER PRIMARY KEY,
	branch_name VARCHAR(25),
	loan_amount INTEGER,
	FOREIGN KEY (branch_name) REFERENCES branch(branch_name)
);

CREATE TABLE borrower(
	customer_name VARCHAR(25),
	loan_number INTEGER,
	FOREIGN KEY (customer_name) REFERENCES customer(customer_name),
	FOREIGN KEY (loan_number) REFERENCES loan(loan_number),
	PRIMARY KEY (customer_name, loan_number)
);

CREATE TABLE account(
	account_number INTEGER PRIMARY KEY,
	branch_name VARCHAR(25),
	balance INTEGER,
	FOREIGN KEY (branch_name) REFERENCES branch(branch_name)
);

CREATE TABLE depositor(
	customer_name VARCHAR(25),
	account_number INTEGER,
	FOREIGN KEY (customer_name) REFERENCES customer(customer_name),
	FOREIGN KEY (account_number) REFERENCES account(account_number)
);

CREATE TABLE employee(
	employee_name VARCHAR(25),
	branch_name VARCHAR(25),
	dob DATE,
	salary INTEGER,
	FOREIGN KEY (branch_name) REFERENCES branch(branch_name),
	PRIMARY KEY (employee_name, branch_name)
);

SELECT * FROM TAB;