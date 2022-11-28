SET SERVEROUTPUT ON;

DROP TABLE employee CASCADE CONSTRAINTS;

CREATE TABLE employee (
    employee_id int PRIMARY KEY,
    employee_name VARCHAR(20),
    salary int
);

INSERT INTO employee 

DECLARE
    empid int := &empid;
BEGIN
    IF ((SELECT COUNT(*) FROM employee WHERE employee_id=empid)) THEN
        dbms_output.put_line("Employee record found!!");
        dbms_output.put_line("Salary: " || )
    ELSE
        dbms_output.put_line("Employee NOT found!!");
    END IF;
END;
/