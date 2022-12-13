CLEAR SCR

-- Drop old tables
DROP TABLE branch CASCADE CONSTRAINTS;
DROP TABLE customer CASCADE CONSTRAINTS;
DROP TABLE loan CASCADE CONSTRAINTS;
DROP TABLE borrower CASCADE CONSTRAINTS;
DROP TABLE account CASCADE CONSTRAINTS;
DROP TABLE depositor CASCADE CONSTRAINTS;
DROP TABLE employee CASCADE CONSTRAINTS;
DROP TABLE company CASCADE CONSTRAINTS;
DROP TABLE works CASCADE CONSTRAINTS;
DROP TABLE manages CASCADE CONSTRAINTS;

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
	customer_street VARCHAR(20)
);

CREATE TABLE loan(
	loan_number INTEGER PRIMARY KEY,
	branch_name VARCHAR(20),
	loan_amount NUMBER(5),
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

-- Employee Database
CREATE TABLE employee(
	employee_name VARCHAR(20) PRIMARY KEY,
	street VARCHAR(20),
	city VARCHAR(20)
);

CREATE TABLE company(
	company_name VARCHAR(20) PRIMARY KEY,
	city VARCHAR(20),
	country VARCHAR(20)
);

CREATE TABLE works(
	employee_name VARCHAR(20) PRIMARY KEY,
	company_name VARCHAR(20),
	salary INTEGER,
	FOREIGN KEY (employee_name) REFERENCES employee(employee_name),
	FOREIGN KEY (company_name) REFERENCES company(company_name)
);

CREATE TABLE manages(
	employee_name VARCHAR(20) PRIMARY KEY,
	manager_name VARCHAR(20),
	FOREIGN KEY (employee_name) REFERENCES employee(employee_name),
	FOREIGN KEY (manager_name) REFERENCES employee(employee_name)
);

SELECT * FROM TAB;