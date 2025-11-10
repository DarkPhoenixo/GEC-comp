$CREATE PROCEDURE project_check () BEGIN
select * from project ;
END$
call project_check()$


$CREATE PROCEDURE Employeedets (IN empid INT)
BEGIN
    SELECT * FROM Employee WHERE empno = empid;
END$
call Employeedets(101)$


$CREATE PROCEDURE Project_info(IN projectnum INT)
BEGIN
select p.proj_num,d.dname,p.dnum,count(w.eno) as empcount from project p inner join dept d on p.dnum =d.deptno inner join workson w on w.pno=p.Proj_num where p.Proj_num=projectnum;
END$
call Project_info(1)$


$CREATE PROCEDURE update_salary_by_empid (
    IN target_empid INT
)
BEGIN
    DECLARE current_salary DECIMAL(10, 2);
    DECLARE num_projects INT;
    DECLARE new_salary DECIMAL(10, 2);
    DECLARE Empname VARCHAR(100);

    SELECT e.salary,COUNT(w.pno),e.Empname INTO  current_salary, num_projects, Empname FROM  employee e   LEFT JOIN  workson w ON e.Empno = w.eno  WHERE e.Empno = target_empid  GROUP BY e.Empno, e.salary, e.Empname;
    SET new_salary = current_salary * (1 + 
            CASE
                WHEN current_salary < 50000 AND num_projects >= 2 THEN 0.05 
                WHEN current_salary > 50000 AND current_salary <= 60000 AND num_projects >= 2 THEN 0.02
                WHEN current_salary > 100000 AND num_projects >= 1 THEN 0.01
                ELSE 0.0
            END
        );
    UPDATE employee SET salary = new_salary WHERE Empno = target_empid;
    SELECT target_empid AS empid,Empname,current_salary as old_salary, new_salary AS increased_salary;
END$
call update_salary_by_empid(101)$


$CREATE PROCEDURE update_salary_for_all()
BEGIN
    DECLARE done INT DEFAULT 0;
    DECLARE empid INT;


    DECLARE emp_cursor CURSOR FOR SELECT Empno FROM employee;
    DECLARE CONTINUE HANDLER FOR NOT FOUND SET done = 1;

    OPEN emp_cursor;

    read_loop: LOOP
        FETCH emp_cursor INTO empid;
        IF done THEN
            LEAVE read_loop;
        END IF;

        CALL update_salary_by_empid(empid); 
    END LOOP;

    CLOSE emp_cursor;
    SELECT Empno, Empname, salary AS new_salary, 'Salary Updated' AS Status FROM employee;

END $

   call update_salary_for_all() $
