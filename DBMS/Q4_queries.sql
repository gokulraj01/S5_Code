-- Queries

-- *a. Find the names, street address and cities of residence for all employees who work for ‘UNIVERSAL Corporation’ and earn more than 10000 Rupees.
SELECT employee_name, street, city
FROM employee, works
WHERE employee.employee_name = works.employee_name AND company_name='Universal' AND salary > 10000;

-- *b. Find the names of all employees in the database who live in the same cities as the companies for which they work.
SELECT employee.employee_name
FROM employee, works, company
WHERE employee.employee_name = works.employee_name AND company.company_name = works.company_name AND employee.city = company.city;

-- *c. Find the names of all employees in the database who live in the same cities and on the same streets as do their managers.
SELECT employee_name
FROM employee, manages
WHERE employee.employee_name = manages.employee_name AND (employee.city, employee.street) IN (
	SELECT city, street FROM employee WHERE employee_name IN manager_name
);

-- *d. Find the names of all employees in the database who do not work for ‘ABC Corporation’. Assume that all people work for exactly one company.
SELECT employee_name
FROM employee, works
WHERE employee.employee_name = works.employee_name AND company_name NOT LIKE 'ABC%'

-- *e. Find the names of all employees in the database who earn more than every employee of ‘GOOGLE Corporation’. Assume that all people work for at most one company.
SELECT employee_name FROM employee, works
WHERE employee.employee_name = works.employee_name AND salary > ALL (
	SELECT salary
	FROM employee, works
	WHERE employee.employee_name = works.employee_name AND company_name LIKE "GOOGLE%"
);

-- *f. Assume that the companies may be located in several cities. Find all companies located in every city in which ‘ABC Corporation’ is located.
SELECT company_name FROM company c1
WHERE (SELECT city FROM company WHERE company_name = c1.company_name) = ALL(SELECT city FROM company WHERE company_name LIKE "ABC%");

-- *g. Find the names of all employees who earn more than the average salary of all employees of their company. Assume that all people work for at most one company.


-- h. Find the name of the company that has the smallest payroll.
SELECT company_name, payroll
FROM (SELECT company_name, SUM(salary) AS payroll FROM works GROUP BY company_name)
WHERE payroll >= ALL (SELECT SUM(salary) FROM works GROUP BY company_name);

-- i. Find the company that has the most employees.
SELECT company_name, roll
FROM (SELECT company_name, COUNT(*) AS roll FROM WORKS GROUP BY company_name)
WHERE roll >= ALL (SELECT COUNT(*) AS roll FROM WORKS GROUP BY company_name);

-- j. Find those companies whose employees earn a higher salary, on average, than the average salary at ‘GOOGLE Corporation
SELECT company_name, avgpay
FROM (SELECT company_name, AVG(salary) AS avgpay FROM works GROUP BY company_name)
WHERE avgpay >= ALL (SELECT AVG(salary) FROM works GROUP BY company_name);