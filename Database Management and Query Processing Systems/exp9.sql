CREATE USER 'Chinmay'@'localhost' IDENTIFIED BY 'Chinmay123';
CREATE USER 'Chirag'@'localhost' IDENTIFIED BY 'Chirag123';
CREATE USER 'Audumber'@'localhost' IDENTIFIED BY 'Audumber123';


GRANT ALL PRIVILEGES ON Atharv.view1 TO 'Chinmay'@'localhost';

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

mysql -u root -p
FLUSH PRIVILEGES;


CREATE INDEX idx_empname ON employee (Empname);

SELECT user, host FROM mysql.user WHERE user IN ('Chinmay', 'Chirag', 'Audumber');


SHOW GRANTS FOR 'Chinmay'@'localhost';
SHOW GRANTS FOR 'Chirag'@'localhost';
SHOW GRANTS FOR 'Audumber'@'localhost';