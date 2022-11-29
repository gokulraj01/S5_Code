-- a. Display details of all customers.
SELECT * FROM customer;

-- b. Find bank accounts with a balance under 1000 rupees. 
SELECT * FROM account WHERE balance < 1000;

-- c. Find names of customers whose city is in Bangalore.
SELECT customer_name FROM customer WHERE customer_city='Bangalore';

-- d. Find the number of tuples in the customer relation. 
SELECT COUNT(*) FROM customer;

-- e. List the street and city where John lives. 
SELECT customer_street, customer_city FROM customer WHERE customer_name LIKE 'John%';

-- f. List the customers whose names ends with letter ‘E’ and has exactly 4 characters. 
SELECT customer_name FROM customer WHERE customer_name LIKE '___e';

-- g. Find total number of customers who have taken a loan. 
SELECT COUNT(UNIQUE customer_name) AS cust_count FROM borrower;

-- h. Find the names of all customers whose street includes the substring ‘Nagar’. 
SELECT customer_name FROM customer WHERE customer_street LIKE '%Nagar%';

-- i. Find all employees whose salary is greater than 1400 and working branch is not ‘Mumbai’.
SELECT employee_name FROM employee, branch
WHERE employee.branch_name = branch.branch_name AND branch_city NOT LIKE '%Mumbai';

-- j. Calculate the average salary of all employees and show the average salary as “avg_salary”. 
SELECT AVG(salary) AS avg_salary FROM employee;

-- k. Find the account number and balance for all accounts from Kolkata branch where the balance is greater than 1000 Rupees. 
SELECT account_number, balance FROM account WHERE branch_name IN (
	SELECT branch_name FROM branch WHERE branch_city='Kolkata'
);

-- l. Find the name of all branches with assets between 10 lakhs and 25 lakhs. 
SELECT branch_name FROM branch WHERE assets >= 1000000 AND assets <= 2500000;

-- m. Find the number of depositors for each branch. 
SELECT branch_name, COUNT(customer_name) AS depositors FROM depositor, account
WHERE depositor.account_number = account.account_number GROUP BY branch_name;

-- n. Find the names of all customers who have both a loan and an account. 
(SELECT UNIQUE customer_name FROM borrower) INTERSECT (SELECT UNIQUE customer_name FROM depositor);

-- alternative (does not work)
-- SELECT customer_name FROM borrower INNER JOIN depositor ON borrower.customer_name = depositor.customer_name;

-- o. Find the names of all customers who have an account but no loan. 
(SELECT UNIQUE customer_name FROM depositor) EXCEPT (SELECT UNIQUE customer_name FROM borrower);

-- *p. List in alphabetic order the names of all customers having a loan in Delhi branch. 
SELECT customer_name FROM borrower WHERE (
	SELECT branch_name FROM branch
	WHERE branch_name IN (SELECT branch_name FROM loan WHERE loan.loan_number = loan_number) AND branch.branch_city='Delhi'
) ORDER BY customer_name;

-- *q. Find the names of all branches that have greater assets than some branch located in Bangalore. 
SELECT branch_name FROM branch WHERE assets > ALL (SELECT assets FROM branch WHERE branch_city='Bangalore');

-- *r. List the name of employees who are born in January. 
SELECT employee_name FROM employee WHERE EXTRACT(MONTH FROM dob)='01';

-- *s. List the name of employees whose age is greater than 30. 
SELECT * FROM (SELECT employee_name, EXTRACT(YEAR FROM (SELECT CURRENT_DATE FROM DUAL)) - EXTRACT(YEAR FROM dob) AS age FROM employee) WHERE age > 30;

-- *t. Display month of birth of all employees.
SELECT employee_name, TO_CHAR(dob, 'Month') AS MOB FROM employee;