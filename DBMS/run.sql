clear scr

-- SELECT branch_name FROM branch
-- WHERE branch_name IN (SELECT branch_name FROM loan WHERE loan.loan_number = borrower.loan_number) AND branch.branch_city='Delhi';

SELECT customer_name FROM borrower WHERE borrower.branch_name IN (
	SELECT branch_name FROM branch
	WHERE branch_name IN (SELECT branch_name FROM loan WHERE loan.loan_number = borrower.loan_number) AND branch.branch_city='Delhi'
);