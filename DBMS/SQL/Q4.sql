CLEAR SCR

-- Drop old tables
DROP TABLE employee CASCADE CONSTRAINTS;
DROP TABLE company CASCADE CONSTRAINTS;
DROP TABLE works CASCADE CONSTRAINTS;
DROP TABLE manages CASCADE CONSTRAINTS;

-- PURGE recyclebin
PURGE RECYCLEBIN;

-- Employee Database
CREATE TABLE employee(
	employee_name VARCHAR(20) PRIMARY KEY,
	street VARCHAR(20),
	city VARCHAR(20)
);

CREATE TABLE company(
	company_name VARCHAR(20) PRIMARY KEY,
	city VARCHAR(20)
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