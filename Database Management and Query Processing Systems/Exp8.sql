create view view1 as select * from employee where deptno=(select deptno from dept where dname='admin');
SELECT TABLE_NAME, IS_UPDATABLE FROM INFORMATION_SCHEMA.VIEWS WHERE TABLE_SCHEMA = 'company' AND TABLE_NAME = 'view1';

create view view2 as select proj_num,pname,project.location,empname,dname,salary from employee natural join dept join workson on empno=eno join project on pno=proj_num;
SELECT TABLE_NAME, IS_UPDATABLE FROM INFORMATION_SCHEMA.VIEWS WHERE TABLE_SCHEMA = 'company' AND TABLE_NAME = 'view2';

create view view3 as select deptno,dname,count(empno)as no_of_emps,avg(salary) as avgsal from employee natural join dept group by deptno; 
SELECT TABLE_NAME, IS_UPDATABLE FROM INFORMATION_SCHEMA.VIEWS WHERE TABLE_SCHEMA = 'company' AND TABLE_NAME = 'view3';

create view view4 as select empname,empno,salary,pno,pname as works_on,hours_per_week from employee join workson on empno=eno join project on pno=proj_num;

create view view5 as select pno,pname,count(empno) as no_of_emps,sum(hours_per_week) as tot_time from view4 group by pno; 

create view view6 as select empno,empname, count(pno) as no_of_projs, sum(hours_per_week) as tot_time from view4 group by empno;

create temporary table temp1 as select empno,empname,pname,hours_per_week from employee join workson on empno=eno join project on pno=proj_num where location='BANGALORE'; 

select empname from temp1 group by empno having count(*)=(select count(*) from project where location='BANGALORE');

select (select pname from project where v.pno=proj_num ) as pname from view5 v where no_of_emps in (select min(no_of_emps) from view5);

select empname from view6 where no_of_projs in(select max(no_of_projs) from view6);

select deptno,dname from view3 where avgsal>(select avg(salary) from employee);