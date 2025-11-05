CREATE USER 'emp1'@'localhost' IDENTIFIED BY 'emp1W';
CREATE USER 'emp2'@'localhost' IDENTIFIED BY 'emp2W';
CREATE USER 'emp3'@'localhost' IDENTIFIED BY 'emp3W';


GRANT ALL PRIVILEGES ON Atharv.view1 TO 'emp1'@'localhost';

 GRANT SELECT ON Atharv.employee TO 'emp2'@'localhost';
GRANT UPDATE (Empname, deptno) ON Atharv.employee TO 'emp2'@'localhost' WITH GRANT OPTION;


EXIT;
mysql -u emp2 -p
-- Enter password: emp2W
GRANT SELECT ON Atharv.employee TO 'emp1'@'localhost';
GRANT UPDATE (Empname, deptno) ON Atharv.employee TO 'emp1'@'localhost';
EXIT;

mysql -u root -p
FLUSH PRIVILEGES;


SHOW GRANTS FOR 'emp1'@'localhost';
SHOW GRANTS FOR 'emp2'@'localhost';
SHOW GRANTS FOR 'emp3'@'localhost';

FLUSH PRIVILEGES;

mysql -u root -p
FLUSH PRIVILEGES;


CREATE INDEX idx_empname ON employee (Empname);

SELECT user, host FROM mysql.user WHERE user IN ('emp1', 'emp2', 'emp3');


SHOW GRANTS FOR 'emp1'@'localhost';
SHOW GRANTS FOR 'emp2'@'localhost';
SHOW GRANTS FOR 'emp3'@'localhost';