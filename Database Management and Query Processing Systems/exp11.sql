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

INSERT INTO table3 (a3) VALUES (150), (202), (303)$
INSERT INTO table4 (a4, b4) VALUES (150, 10), (999, 20)$
INSERT INTO table1 (a1) VALUES (150)$




CREATE TABLE emp_proj AS  SELECT  eno AS empid, COUNT(pno) AS number_of_projects,SUM(hours_per_week) AS total_number_of_hrs FROM worksonGROUP BY eno$
ALTER TABLE emp_proj ADD PRIMARY KEY (empid)$

CREATE TABLE proj_info AS SELECT pno AS project_number,COUNT(eno) AS number_of_employees,SUM(hours_per_week) AS total_number_of_hrs_spent FROM workson GROUP BY pno$
ALTER TABLE proj_info ADD PRIMARY KEY (project_number)$

$CREATE TRIGGER trg2
AFTER DELETE ON workson
FOR EACH ROW
BEGIN
    
    UPDATE emp_proj
    SET 
        number_of_projects = (SELECT COUNT(pno) FROM workson WHERE eno = OLD.eno),
        total_number_of_hrs = (SELECT IFNULL(SUM(hours_per_week), 0) FROM workson WHERE eno = OLD.eno)
    WHERE empid = OLD.eno;
    
   
    UPDATE proj_info
    SET 
        number_of_employees = (SELECT COUNT(eno) FROM workson WHERE pno = OLD.pno),
        total_number_of_hrs_spent = (SELECT IFNULL(SUM(hours_per_week), 0) FROM workson WHERE pno = OLD.pno)
    WHERE project_number = OLD.pno;
    
END$