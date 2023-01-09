SET SERVEROUTPUT ON;

DROP TABLE employee CASCADE CONSTRAINTS;

CREATE TABLE employee (
    employee_id NUMBER(4) PRIMARY KEY,
    employee_name VARCHAR(20),
    salary int
);

INSERT INTO employee VALUES (1122, 'Manoj', 15000);
INSERT INTO employee VALUES (5566, 'Archa', 2605);
INSERT INTO employee VALUES (1234, 'Ali', 1500);
INSERT INTO employee VALUES (9785, 'Saranya', 44523);
INSERT INTO employee VALUES (5623, 'Suraj', 132552);

DECLARE
	emp_id INT := &emp_id;
	n INT;
	emp_tup employee%ROWTYPE;
	e EXCEPTION;
BEGIN
	SELECT COUNT(*) INTO n FROM employee WHERE employee_id=emp_id;
	IF (n = 0) THEN
		RAISE e;
	ELSE
		SELECT * INTO emp_tup FROM employee WHERE employee_id=emp_id;
		dbms_output.put_line('Name: ' || emp_tup.employee_name);
		dbms_output.put_line('Salary: ' || emp_tup.salary);
	END IF;
EXCEPTION
	WHEN e THEN
		dbms_output.put_line('No such employee!!');
END;
/