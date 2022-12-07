clear scr
SET SERVEROUTPUT ON;

--SELECT customer_name FROM borrower
--WHERE (
--    SELECT branch_name FROM branch
--	WHERE branch_name IN (
--	    SELECT branch_name FROM loan WHERE loan.loan_number = loan_number
--    ) AND branch.branch_city='Delhi'
--) ORDER BY customer_name;


-- List in alphabetic order the names of all customers having a loan in Delhi branch.
SELECT customer_name FROM borrower
WHERE loan_number IN (
    SELECT loan_number FROM loan WHERE branch_name IN (
        SELECT branch_name FROM branch WHERE branch_city = 'Delhi'
    )
) ORDER BY customer_name;
