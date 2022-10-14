CLEAR SCR

-- Add customer area into CUSTOMER
ALTER TABLE customer ADD(
	customer_area VARCHAR(20)
);

-- Change loan_amount to INTEGER in LOAN
ALTER TABLE loan MODIFY(
	loan_amount INTEGER
);

-- Rename customer_area to customer_city
ALTER TABLE customer RENAME COLUMN customer_area TO customer_city;

SELECT * FROM TAB;