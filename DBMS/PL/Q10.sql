SET SERVEROUTPUT ON;

DROP TABLE employee CASCADE CONSTRAINTS;

CREATE TABLE employee (
    employee_id NUMBER(4) PRIMARY KEY,
    employee_name VARCHAR(20),
    salary int
);

INSERT INTO employee VALUES (1122, 'Manoj', 1500);
INSERT INTO employee VALUES (5566, 'Archa', 2605);
INSERT INTO employee VALUES (1234, 'Ali', 1500);
INSERT INTO employee VALUES (9785, 'Saranya', 40000);
INSERT INTO employee VALUES (5623, 'Suraj', 1325);

DECLARE
	n int;
	salary int;
	PROCEDURE incSalary AS
	BEGIN
		-- Get no: of employees with salary > 10000
		SELECT COUNT(*) INTO n FROM employee WHERE salary > 10000;
		
		-- Give 6% raise if only one employee
		IF ( n = 0) THEN
			dbms_output.put_line('No such employee!!');
		ELSIF ( n = 1 ) THEN
			UPDATE employee SET salary=salary*1.06 WHERE salary > 10000;
			dbms_output.put_line('6% raise given!!');
		ELSE
			dbms_output.put_line('Too many employees!!');
		END IF;
	END;
BEGIN
	incSalary;
END;
/

SELECT * FROM employee;