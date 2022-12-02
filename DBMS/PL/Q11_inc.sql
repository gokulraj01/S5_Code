-- Incomplete Q11
clear scr

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
	i INT;
	tn VARCHAR(20) := 'employee';

	FUNCTION GETN(tname IN VARCHAR) RETURN INTEGER IS
		n INT;
	BEGIN
		EXECUTE IMMEDIATE 'SELECT COUNT(*) FROM :val' USING tname;
		RETURN n;
	END;
BEGIN
	i := GETN(tn);
	dbms_output.put_line('Table "' || tn || '" has ' || i || ' tuples!!');
END;
/