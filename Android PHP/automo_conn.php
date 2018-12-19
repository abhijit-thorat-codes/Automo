<?php

$db_name = "csv_db";
$username = "root";
$password = "";
$server_name = "localhost";

$conn = mysqli_connect($server_name,$username,$password,$db_name);
if($conn)
		echo"Connection Successful!";
else
		echo"Connection Failed!";
?>

http://tinyurl.com/yc8vff669