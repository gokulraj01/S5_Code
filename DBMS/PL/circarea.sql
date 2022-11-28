SET SERVEROUTPUT ON;

DROP TABLE circlearea CASCADE CONSTRAINTS; 

CREATE TABLE circlearea (
        radius float,
        area float
);

clear scr

DECLARE
    radius float;
    area float;
    n1 int;
    n2 int;
BEGIN
    n1 := &n1;
    n2 := &n2;
    radius := n1;
    while (radius <= n2) LOOP
        area := 3.14*radius*radius;
        INSERT INTO circlearea VALUES (radius, area);
        radius := radius+1;
    END LOOP;
END;
/

SELECT * FROM circlearea;