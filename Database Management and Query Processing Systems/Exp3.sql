create table Project(
    Pno int,
    Pname varchar(25) NOT NULL UNIQUE,
    location varchar(25),
    dnum int,
    PRIMARY KEY (Pno),
    foreign key (dnum) references dept(deptno)
);

create table works_on(
    eno int,
    pno int,
    hours_per_week float,
    PRIMARY KEY (eno, pno),
    foreign key (eno) references Employee(Empno),
    foreign key (pno) references Project(Pno)
);

ALTER TABLE Employee ADD CONSTRAINT fk_deptno FOREIGN KEY (deptno) REFERENCES dept(deptno);
ALTER TABLE Employee ADD COLUMN bdate DATE;
ALTER table dept add UNIQUE (dname);
alter table works_on alter column hours_per_week set default 20;
alter table Project change column Pno Proj_num tinyint;
alter table works_on rename to workson;


ALTER TABLE employee DROP FOREIGN KEY fk_deptno;
ALTER TABLE project  DROP FOREIGN KEY project_ibfk_1;
ALTER TABLE dept MODIFY deptno TINYINT;
ALTER TABLE employee MODIFY deptno TINYINT;
ALTER TABLE project  MODIFY dnum TINYINT;

ALTER TABLE employee 
ADD CONSTRAINT fk_deptno 
FOREIGN KEY (deptno) REFERENCES dept(deptno);
ALTER TABLE project 
ADD CONSTRAINT project_ibfk_1 
FOREIGN KEY (dnum) REFERENCES dept(deptno);


ALTER TABLE employee
DROP COLUMN bdate;

mysqldump -u root -p company > dump.sql
CREATE DATABASE dummyemp;
mysql -u root -p dummyemp < dump.sql

DROP DATABASE dummyemp;
CREATE TABLE dummyproject AS SELECT * FROM Project;
select * from dummyproject;

DELETE FROM dummyproject;
INSERT INTO dummyproject SELECT * FROM Project;