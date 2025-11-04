MySQL -u root
create database company1
use company1
CREATE TABLE Employee (
    Empno INT,
    Empname VARCHAR(25) NOT NULL,
    Gender VARCHAR(1),
    job VARCHAR(25),
    managerno INT,
    hiredate DATE,
    salary FLOAT(12,2),
    commision FLOAT(10,2),
    deptno TINYINT,
    PRIMARY KEY (Empno)
);

CREATE TABLE dept (
    Deptno INT,
    dname VARCHAR(25) NOT NULL,
    location VARCHAR(20),
    PRIMARY KEY (Deptno)
);

INSERT INTO dept (Deptno, dname, location) VALUES
(5, 'HR', 'Delhi'),
(10, 'Accounts', 'Mumbai'),
(20, 'Sales', 'Pune'),
(30, 'IT', 'Bangalore'),
(40, 'Admin', 'Hyderabad');


INSERT INTO Employee (Empno, Empname, Gender, job, managerno, hiredate, salary, commision, deptno) VALUES
(101, 'ALAN', 'M', 'MANAGER', NULL, '2015-06-10', 45000.00, 3000.00, 10),
(102, 'BETTY', 'F', 'CLERK', 101, '2019-08-20', 18000.00, NULL, 10),
(103, 'CARL', 'M', 'SALESMAN', 101, '2022-03-15', 25000.00, 5000.00, 20),
(104, 'DAVID', 'M', 'CLERK', 101, '2020-01-12', 19000.00, NULL, 20),
(105, 'ELLA', 'F', 'MANAGER', NULL, '2017-07-07', 50000.00, 6000.00, 30),
(106, 'FRANK', 'M', 'PRESIDENT', NULL, '2012-05-25', 80000.00, NULL, 40),
(107, 'GINA', 'F', 'CLERK', 105, '2021-09-17', 22000.00, NULL, 5),
(108, 'HELEN', 'F', 'ANALYST', 105, '2018-02-03', 40000.00, NULL, 30),
(109, 'IRIS', 'F', 'SALESMAN', 105, '2019-04-04', 32000.00, 35000.00, 5),
(110, 'JACK', 'M', 'MANAGER', 106, '2016-11-11', 48000.00, 2000.00, 40),
(111, 'KATE', 'F', 'CLERK', 105, '2023-01-01', 23000.00, NULL, 30),
(112, 'LUKE', 'M', 'ANALYST', 110, '2020-06-06', 41000.00, NULL, 40),
(113, 'MARK', 'M', 'SALESMAN', 110, '2014-10-10', 30000.00, 40000.00, 10),
(114, 'RITA', 'F', 'CLERK', 101, '2023-04-01', 20000.00, NULL, 10),
(115, 'BILL', 'M', 'CLERK', 101, '2022-08-08', 21000.00, NULL, 20);


SELECT * FROM Employee;
SELECT * FROM Dept;
SELECT Empno, Empname, job, hiredate FROM Employee;
SELECT Empno, Empname, job, salary FROM Employee WHERE deptno = 10;
SELECT Empname, salary FROM Employee WHERE job = 'CLERK';
SELECT Deptno, dname FROM Dept WHERE Deptno >= 20;
SELECT Empname FROM Employee WHERE salary < 25000;
SELECT Empname FROM Employee WHERE Gender = 'F' AND deptno = 5 AND salary > 30000;
SELECT Empname, salary, commision FROM Employee WHERE commision > salary;
SELECT Empno, Empname FROM Employee WHERE job = 'PRESIDENT';
SELECT Empname FROM Employee WHERE commision IS NULL;
SELECT Empname FROM Employee WHERE job IN ('ANALYST', 'CLERK');
SELECT DISTINCT job FROM Employee;
SELECT Empname FROM Employee WHERE LENGTH(Empname) = 4;
SELECT Empname FROM Employee WHERE Empname LIKE '%R';
SELECT Empname FROM Employee WHERE Empname LIKE 'B%' OR Empname LIKE 'M%';
SELECT Empname FROM Employee WHERE Empname BETWEEN 'A' AND 'Gzzzz';
SELECT * FROM Employee ORDER BY salary ASC;
SELECT * FROM Employee ORDER BY deptno ASC, Empname ASC;
SELECT Empname, hiredate FROM Employee ORDER BY hiredate DESC;
SELECT Empname, salary, salary * 0.10 AS PF FROM Employee;
SELECT Empname FROM Employee WHERE hiredate <= DATE_SUB(CURDATE(), INTERVAL 2 YEAR);
DELETE FROM Employee WHERE Gender = 'M' AND commision > salary;