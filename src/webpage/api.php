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
            }
            if (array_key_exists("nextmove", $_POST) && $_POST["nextmove"] != "") {
                echo "<p>Next move: ".htmlspecialchars($_POST["nextmove"])."</p>";
                file_put_contents("nextmove", $_POST["nextmove"]);
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