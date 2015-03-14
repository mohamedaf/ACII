<?php
header("HTTP/1.1 303");
header('Location: http://127.0.0.1/~esj/echo.php?' . $_SERVER['QUERY_STRING']);
?>
