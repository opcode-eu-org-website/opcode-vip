
<?php
$sql_conn = mysqli_connect('server', 'user', 'password', 'database');
if (!$sql_conn) {
	echo "ERROR: " . mysqli_connect_error();
	exit;
} else {
	echo "Connected to MySQL: " . mysqli_get_host_info($sql_conn);
}

$query = $db->query("SELECT u.name, p.text FROM users AS u JOIN posts AS p ON (u.uid = p.uid);");
while ($row = $query->fetch_array()) {
	print($row["name"] . ": " . $row["text"] . "\n");
}
?>
