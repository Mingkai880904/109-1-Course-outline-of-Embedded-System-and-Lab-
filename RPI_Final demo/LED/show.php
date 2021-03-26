<html>
<head>
<meta charset="utf8">
</head>
<body>
<table border=3>
<tr>
<th>ID</th>
<th>溫度</th>
<th>濕度</th>
<th>顏色</th>
<th>上傳時間</th>
</tr>
<?php
date_default_timezone_set("asia/taipei");
$dsn='mysql:host=127.0.0.1;dbname=Sensors';
try {
$db=new PDO($dsn,'4070E022','0000');
$db->exec("set names utf8");
$sql="select * from DHT order by Time Desc;";
foreach ($db->query($sql) as $row) {
$Temp = $row["Temp"];
if($row["Temp"]<25)
 {
	$row["color"] = "BLUE";
	}
elseif($row["Temp"]>=25 & $row["Temp"]<30)
{
$row["color"] = "GREEN";
}else{
$row["color"] = "RED";
}

echo "<tr>";
echo " <td>".$row["ID"]."</td>";
echo " <td>".$row["Temp"]."</td>";
echo " <td>".$row["Humidity"]."</td>";
echo " <td>".$row["color"]."</td>";
echo "<td>".$row["Time"]."</td>";
echo "</tr>";
}
} catch (PDOException $e) {
printf("DATABASER_ERRMESG: %s",$e->getMessage());
}
?>
</table>

<input type="button" value="返回上一頁" onclick="location.href='http://192.168.2.180/Sensor.html'">
</body>
</html>
