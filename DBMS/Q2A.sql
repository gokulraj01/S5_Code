CLEAR SCR

-- Add customer area into CUSTOMER
ALTER TABLE customer ADD(
	customer_area VARCHAR(20)
);

-- Change 'loan_amount' to INTEGER in LOAN
ALTER TABLE loan MODIFY(
	loan_amount INTEGER
);

-- Rename 'customer_area' to 'customer_city'
ALTER TABLE customer RENAME COLUMN customer_area TO customer_city;


-- Add new column 'date_of_joining' into Employee
ALTER TABLE employee ADD(
	date_of_joining DATE
);

-- Delete 'country' from Company
ALTER TABLE company DROP COLUMN country;

SELECT * FROM TAB;