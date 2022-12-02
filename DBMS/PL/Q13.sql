SET SERVEROUTPUT ON;

DROP TABLE employee CASCADE CONSTRAINTS;

CREATE TABLE employee (
    eid VARCHAR(4) PRIMARY KEY,
    ename VARCHAR(20),
    ecity VARCHAR(20),
	eage INT,
	company VARCHAR(20)
);

INSERT INTO employee VALUES ('E01', 'Manoj', 'Kollam', 45, 'Google');
INSERT INTO employee VALUES ('E02', 'Archa', 'Trivandrum', 45, 'Apple');
INSERT INTO employee VALUES ('E03', 'Ali', 'Kottayam', 45, 'Google');
INSERT INTO employee VALUES ('E04', 'Saranya', 'Alappuzha', 45, 'Microsoft');
INSERT INTO employee VALUES ('E05', 'Suraj', 'Kochi', 45, 'Netflix');

DECLARE
	-- Declare EXCEPTIONS
	e01 EXCEPTION;
	e05 EXCEPTION;
	en EXCEPTION;
	
	emp_id VARCHAR(4) := '&emp_id';
	n INT;
	emp_tup employee%ROWTYPE;
BEGIN
	SELECT * INTO emp_tup FROM employee WHERE eid=emp_id;
	IF (emp_id = 'E01') THEN
		RAISE e01;
	ELSIF (emp_id = 'E05') THEN
		RAISE e05;
	ELSE
		RAISE en;
	END IF;
EXCEPTION
	WHEN e01 THEN
		dbms_output.put_line('City: ' || emp_tup.ecity);
	WHEN e05 THEN
		dbms_output.put_line('Company: ' || emp_tup.company);
	WHEN en THEN
		dbms_output.put_line('Age: ' || emp_tup.eage);
END;
/