CREATE USER 'Chinmay'@'localhost' IDENTIFIED BY 'Chinmay123';
CREATE USER 'Chirag'@'localhost' IDENTIFIED BY 'Chirag123';
CREATE USER 'Audumber'@'localhost' IDENTIFIED BY 'Audumber123';

CREATE VIEW emp_view AS SELECT Empno, Empname, Gender, job, deptno, salary FROM employee WHERE job = 'CLERK';
GRANT ALL PRIVILEGES ON Atharv.emp_view TO 'Chinmay'@'localhost';

 GRANT SELECT ON Atharv.employee TO 'Chirag'@'localhost';
GRANT UPDATE (Empname, deptno) ON Atharv.employee TO 'Chirag'@'localhost' WITH GRANT OPTION;


EXIT;
mysql -u Chirag -p
-- Enter password: Chirag123
GRANT SELECT ON Atharv.employee TO 'Chinmay'@'localhost';
GRANT UPDATE (Empname, deptno) ON Atharv.employee TO 'Chinmay'@'localhost';
EXIT;

mysql -u root -p
FLUSH PRIVILEGES;


SHOW GRANTS FOR 'Chinmay'@'localhost';
SHOW GRANTS FOR 'Chirag'@'localhost';
SHOW GRANTS FOR 'Audumber'@'localhost';

FLUSH PRIVILEGES;


The following are the most common privileges available to grant to users in MySQL/MariaDB:
Data Privileges: SELECT, INSERT, UPDATE, DELETE
Structure Privileges: CREATE, ALTER, DROP (for tables/databases)
Administration Privileges: GRANT OPTION (allows a user to grant their own privileges to others), SUPER, SHUTDOWN, RELOAD


CREATE INDEX idx_empname ON employee (Empname);

SELECT user, host FROM mysql.user WHERE user IN ('Chinmay', 'Chirag', 'Audumber');


SHOW GRANTS FOR 'Chinmay'@'localhost';
SHOW GRANTS FOR 'Chirag'@'localhost';
SHOW GRANTS FOR 'Audumber'@'localhost';