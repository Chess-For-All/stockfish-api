<!DOCTYPE html>
<html lang="en">
<head>
    <meta charset="UTF-8">
    <meta name="viewport" content="width=device-width, initial-scale=1.0">
    <title>api</title>
</head>
<body>
    <?php
        if ($_SERVER["REQUEST_METHOD"] == "POST") {
            if (array_key_exists("bestmove", $_POST) && $_POST["bestmove"] != "") {
                echo "<p>Best move: ".htmlspecialchars($_POST["bestmove"])."</p>";
                file_put_contents("bestmove", $_POST["bestmove"]);
                if (array_key_exists("timestamp", $_POST) && $_POST["timestamp"] != "") {
                    echo "<p>Timestamp: ".htmlspecialchars($_POST["timestamp"])."</p>";
                    file_put_contents("bestmove", file_get_contents("bestmove")."\n".$_POST["timestamp"]);
                } else {
                    echo "<p>Timestamp: ".(new DateTime())->getTimeStamp()."</p>";
                    file_put_contents("bestmove", file_get_contents("bestmove")."\n".(new DateTime())->getTimeStamp());
                }
            }
            if (array_key_exists("nextmove", $_POST) && $_POST["nextmove"] != "") {
                echo "<p>Next move: ".htmlspecialchars($_POST["nextmove"])."</p>";
                file_put_contents("nextmove", $_POST["nextmove"]);
                if (array_key_exists("timestamp", $_POST) && $_POST["timestamp"] != "") {
                    echo "<p>Timestamp: ".htmlspecialchars($_POST["timestamp"])."</p>";
                    file_put_contents("nextmove", file_get_contents("nextmove")."\n".$_POST["timestamp"]);
                } else {
                    echo "<p>Timestamp: ".(new DateTime())->getTimeStamp()."</p>";
                    file_put_contents("nextmove", file_get_contents("nextmove")."\n".(new DateTime())->getTimeStamp());
                }
            }
            
        }
    ?>
    <form method="post">
        <input type="text" name="bestmove">
        <input type="text" name="nextmove">
        <input type="submit">
    </form>
</body>
</html>