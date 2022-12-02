CLEAR SCR

DROP TABLE classroom CASCADE CONSTRAINTS;
DROP TABLE department CASCADE CONSTRAINTS;
DROP TABLE course CASCADE CONSTRAINTS;
DROP TABLE instructor CASCADE CONSTRAINTS;
DROP TABLE section CASCADE CONSTRAINTS;
DROP TABLE teaches CASCADE CONSTRAINTS;

CREATE TABLE classroom(
	building VARCHAR(20),
	room_number INT,
	capcity INT,
	PRIMARY KEY (building, room_number)
);

CREATE TABLE department(
	dept_name VARCHAR(20) PRIMARY KEY,
	building VARCHAR(20),
	budget INT
);

CREATE TABLE course(
	course_id VARCHAR(20) PRIMARY KEY,
	title VARCHAR(20),
	dept_name VARCHAR(20),
	credits INT,
	FOREIGN KEY (dept_name) REFERENCES department(dept_name)
);

CREATE TABLE instructor(
	id INT PRIMARY KEY,
	name VARCHAR(20),
	dept_name VARCHAR(20),
	salary INT,
	FOREIGN KEY (dept_name) REFERENCES department(dept_name)
);

CREATE TABLE section(
	sec_id INT,
	course_id VARCHAR(20),
	semester INT,
	year NUMBER(4),
	building VARCHAR(20),
	room_number INT,
	time_slot_id INT,
	PRIMARY KEY(sec_id, course_id, semester, year),
	FOREIGN KEY (course_id) REFERENCES course(course_id)
);

CREATE TABLE teaches(
	id INT,
	course_id VARCHAR(20),
	sec_id INT,
	semester INT,
	year NUMBER(4),
	PRIMARY KEY (id, course_id, sec_id, semester, year),
	FOREIGN KEY (id) REFERENCES instructor(id),
	FOREIGN KEY (course_id) REFERENCES course(course_id)
);

-- Create view for Physics in courses in 2009
DROP VIEW PHYSICS;
CREATE VIEW PHYSICS AS
SELECT sec_id, course.course_id, semester, year, building, room_number, time_slot_id FROM course, section
WHERE course.course_id = section.sec_id AND year = 2009 AND dept_name = 'Physics';