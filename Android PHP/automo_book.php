<?php
require "book_conn.php";
 $book_name="";
if(isset($_POST['bookName']))
{
	$book_name=$_POST['bookName'];
}
$query="select barcode from mybooks where book_name like '$book_name';";
$result=mysqli_query($conn ,$query);
if(mysqli_num_rows()($result) > 0)
{
	echo $result;
}
else
{
 	echo "Book not found!"; 
}
?>
wkxf4vrxff