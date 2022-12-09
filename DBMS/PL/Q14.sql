SET SERVEROUTPUT ON;

DROP TABLE Book CASCADE CONSTRAINTS;
DROP TABLE Circulation CASCADE CONSTRAINTS;

CREATE TABLE Book (
	book_no INT PRIMARY KEY,
	title VARCHAR(20),
	cost INT
);

CREATE TABLE Circulation(
	user_id INT PRIMARY KEY,
	book_no INT,
	issue_date DATE,
	return_date DATE,
	FOREIGN KEY (book_no) REFERENCES Book(book_no)
);

INSERT INTO Book VALUES (12, 'Book 1', 500);

CREATE TRIGGER Book_trig
BEFORE INSERT ON Book
FOR EACH ROW
DECLARE
	avgc INT;
BEGIN
	SELECT AVG(cost) INTO avgc FROM Book;
	IF(:NEW.cost < avgc) THEN
		RAISE_APPLICATION_ERROR(-20000, 'Cost less than average cost!!');
	END IF;
END;
/

INSERT INTO Book VALUES (13, 'Book 2', 700);
INSERT INTO Book VALUES (14, 'Book 3', 100);