--@Q4.sql;
--@Q4_val.sql;
clear scr

SELECT * FROM works
WHERE salary > (
	SELECT avgpay FROM (SELECT company_name, AVG(salary) AS avgpay FROM works GROUP BY company_name)
	WHERE 
);