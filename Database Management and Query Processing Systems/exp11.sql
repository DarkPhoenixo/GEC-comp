CREATE TABLE table1 (a1 INT PRIMARY KEY)$
CREATE TABLE table2 (a2 INT)$
CREATE TABLE table3 (a3 INT PRIMARY KEY)$
CREATE TABLE table4 (a4 INT PRIMARY KEY, b4 INT DEFAULT 0)$



$CREATE TRIGGER trg1
AFTER INSERT ON table1
FOR EACH ROW
BEGIN
    INSERT INTO table2 (a2) VALUES (NEW.a1);
    DELETE FROM table3 WHERE a3 = NEW.a1;

    UPDATE table4   SET b4 = b4 + 1  WHERE a4 = NEW.a1;
END$


DELETE FROM table3$
DELETE FROM table4$

INSERT INTO table3 (a3) VALUES (101), (202), (303)$
INSERT INTO table4 (a4, b4) VALUES (101, 10), (999, 20)$
INSERT INTO table1 (a1) VALUES (101), (404)$



CREATE TABLE emp_proj (
    empid INT PRIMARY KEY,
    number_of_projects INT DEFAULT 0,
    total_number_of_hrs DECIMAL(10, 2) DEFAULT 0.00
)$

CREATE TABLE proj_info (
    project_number INT PRIMARY KEY,
    number_of_employees INT DEFAULT 0,
    total_number_of_hrs_spent DECIMAL(10, 2) DEFAULT 0.00
)$


$CREATE TRIGGER trg2
AFTER DELETE ON workson
FOR EACH ROW
BEGIN

    UPDATE emp_proj AS ep
    SET 
        ep.number_of_projects = (SELECT COUNT(pno) FROM workson WHERE eno = OLD.eno),
        ep.total_number_of_hrs = (SELECT SUM(hours_per_week) FROM workson WHERE eno = OLD.eno)
    WHERE ep.empid = OLD.eno;
    

    UPDATE proj_info AS pi
    SET 
        pi.number_of_employees = (SELECT COUNT(eno) FROM workson WHERE pno = OLD.pno),
        pi.total_number_of_hrs_spent = (SELECT SUM(hours_per_week) FROM workson WHERE pno = OLD.pno)
    WHERE pi.project_number = OLD.pno;
    
END$


INSERT INTO emp_proj (empid, number_of_projects, total_number_of_hrs) VALUES (101, 4, 105.00)$
INSERT INTO proj_info (project_number, number_of_employees, total_number_of_hrs_spent) VALUES (4, 3, 36.00)$
DELETE FROM workson WHERE eno = 101 AND pno = 4;