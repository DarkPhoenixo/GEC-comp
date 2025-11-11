<?php
// Database connection
$conn = new mysqli('localhost', 'root', '', 'Atharv');

if ($conn->connect_error) {
    die("Connection failed: " . $conn->connect_error);
}

$action = $_POST['action'];
$deptno = $_POST['deptno'];
$dname = $_POST['dname'];
$location = $_POST['location'];

// Perform action
if ($action == 'insert') {
    $sql = "INSERT INTO dept (deptno, dname, location) VALUES ($deptno, '$dname', '$location')";
    $conn->query($sql);
    echo "Inserted successfully!";
}

if ($action == 'update') {
    $sql = "UPDATE dept SET dname='$dname', location='$location' WHERE deptno=$deptno";
    $conn->query($sql);
    echo "Updated successfully!";
}

if ($action == 'delete') {
    $sql = "DELETE FROM dept WHERE deptno=$deptno";
    $conn->query($sql);
    echo "Deleted successfully!";
}

if ($action == 'view') {
    $result = $conn->query("SELECT * FROM dept");
    
    echo "<h3>All Departments</h3>";
    echo "<table>";
    echo "<tr><th>Dept No</th><th>Name</th><th>Location</th></tr>";
    
    while ($row = $result->fetch_assoc()) {
        echo "<tr>";
        echo "<td>" . $row['deptno'] . "</td>";
        echo "<td>" . $row['dname'] . "</td>";
        echo "<td>" . $row['location'] . "</td>";
        echo "</tr>";
    }
    
    echo "</table>";
}

echo "<br><br><a href='index.html'>Go Back</a>";

$conn->close();
?>