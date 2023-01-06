SET SERVEROUTPUT ON;

DROP PACKAGE employee_pack;

CREATE PACKAGE employee_pack AS
	PROCEDURE inc_sal;
	FUNCTION check_id(eid INT) RETURN INT;
END;
/

CREATE OR REPLACE PACKAGE BODY employee_pack AS
	PROCEDURE inc_sal AS
	BEGIN
		UPDATE employee SET salary=salary*1.05 WHERE salary < 10000;
		dbms_output.put_line('Salary updated!!');
	END;
	
	FUNCTION check_id(eid INT) RETURN INT AS
		n INT;
		name employee.employee_name%type;
	BEGIN
		SELECT COUNT(*) INTO N FROM employee WHERE employee_id=eid;
		IF (n = 0) THEN
			dbms_output.put_line('#'|| eid || ' does not exist');
			RETURN 0;
		ELSE
			SELECT employee_name INTO name FROM employee WHERE employee_id=eid;
			dbms_output.put_line('Name: '|| name ||'. Employee exists!');
			RETURN 1;
		END IF;
	END;
END;
/

DECLARE
	t INT;
BEGIN
	employee_pack.inc_sal;
	t := employee_pack.check_id(5566);
	t := employee_pack.check_id(9999);
END;
/