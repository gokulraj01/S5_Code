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
	n int;
	salary int;
    empid int := &empid;
BEGIN
	-- Get salary of user specified employee
	SELECT COUNT(*) INTO n FROM employee WHERE employee_id=empid;
    IF (n > 0) THEN
		SELECT salary INTO salary FROM employee WHERE employee_id=empid;
        dbms_output.put_line('Employee record found!!');
        dbms_output.put_line('Salary: ' || salary);
    ELSE
        dbms_output.put_line('Employee NOT found!!');
    END IF;
	
	-- Increment 1000 to all employees with salary less than 10000
	n := 0;
	FOR emp IN (SELECT * FROM employee) LOOP
		IF (emp.salary < 10000) THEN
			dbms_output.put_line('#' || emp.employee_id || ' has low salary. Giving 1k.');
			UPDATE employee SET salary=salary+1000 WHERE employee_id = emp.employee_id;
			n := n+1;
		END IF;
	END LOOP;
	dbms_output.put_line(n || ' employees got a raise!!');
END;
/

SELECT * FROM employee;