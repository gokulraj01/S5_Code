SET SERVEROUTPUT ON;

DECLARE
	n1 int := &n1;
	n2 int := &n2;
	s int;
	a int;
	m int;
	
	PROCEDURE ops(x IN INT, y IN INT, s OUT INT, av OUT FLOAT, mn OUT INT) IS
	BEGIN
		s := x+y;
		av := s/2;
		IF (x < y) THEN
			mn := x;
		ELSE
			mn := y;
		END IF;
	END;
BEGIN
	ops(n1, n2, s, a, m);
	dbms_output.put_line('Sum: ' || s);
	dbms_output.put_line('Average: ' || a);
	dbms_output.put_line('Minimum: ' || m);
END;
/