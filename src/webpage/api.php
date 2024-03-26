<!DOCTYPE html>
<html lang="en">

<head>
    <!-- jQuery -->
    <script src="https://code.jquery.com/jquery-3.7.1.js"
        integrity="sha256-eKhayi8LEQwp4NKxN+CfCh+3qOVUtJn3QNZ0TciWLP4=" crossorigin="anonymous"></script>
    <!-- chess -->
    <link rel="stylesheet" href="https://unpkg.com/@chrisoakman/chessboardjs@1.0.0/dist/chessboard-1.0.0.min.css"
        integrity="sha384-q94+BZtLrkL1/ohfjR8c6L+A6qzNH9R2hBLwyoAfu3i/WCvQjzL2RQJ3uNHDISdU" crossorigin="anonymous">
    <script src="https://code.jquery.com/jquery-3.5.1.min.js"
        integrity="sha384-ZvpUoO/+PpLXR1lu4jmpXWu80pZlYUAfxl5NsBMWOEPSjUn/6Z/hRTt8+pR6L4N2"
        crossorigin="anonymous"></script>

    <script src="https://unpkg.com/@chrisoakman/chessboardjs@1.0.0/dist/chessboard-1.0.0.min.js"
        integrity="sha384-8Vi8VHwn3vjQ9eUHUxex3JSN/NFqUg3QbPyX8kWyb93+8AC/pPWTzj+nHtbC5bxD"
        crossorigin="anonymous"></script>
    <meta charset="UTF-8">
    <meta name="viewport" content="width=device-width, initial-scale=1.0">
    <title>api</title>
</head>

<body>
    <div id="myBoard" style="width: 400px"></div>
    <?php
    if ($_SERVER["REQUEST_METHOD"] == "POST") {
        if (array_key_exists("bestmove", $_POST) && $_POST["bestmove"] != "") {
            echo "<p>Best move: " . htmlspecialchars($_POST["bestmove"]) . "</p>";
            if (strlen($_POST["bestmove"]) >= 5) {
                file_put_contents("bestmove", $_POST["bestmove"]);
            } else {
                file_put_contents("bestmove", $_POST["bestmove"] + " ");
            }
        }
        if (array_key_exists("whitemove", $_POST) && $_POST["whitemove"] != "") {
            echo "<p>White move: " . htmlspecialchars($_POST["whitemove"]) . "</p>";
            file_put_contents("whitemove", $_POST["whitemove"]);
        }
        if (array_key_exists("blackmove", $_POST) && $_POST["blackmove"] != "") {
            echo "<p>Black move: " . htmlspecialchars($_POST["blackmove"]) . "</p>";
            file_put_contents("blackmove", $_POST["blackmove"]);
        }

    }
    echo "<p id=\"status\">Best move: " . (htmlspecialchars(file_exists("bestmove") ? file_get_contents("bestmove") : "")) . "<br>White Move: " . htmlspecialchars(file_exists("whitemove") ? file_get_contents("whitemove") : "") . "<br>Black Move: " . htmlspecialchars(file_exists("blackmove") ? file_get_contents("blackmove") : "") . "</p>"
        ?>
    <script>
        function postMove(start, end) {
            var startpos;
            var endpos;
            Object.keys(start).forEach(key => {
                if (!end[key]) {
                    startpos = key;
                }
            });
            Object.keys(end).forEach(key => {
                if (!start[key]) {
                    endpos = key;
                }
            });
            if (!endpos) {
                Object.keys(end).forEach(key => {
                    if (start[key] != end[key]) {
                        endpos = key;
                    }
                })
            }
            console.log(startpos + endpos);
            if (start[startpos][0] == 'w') {
                console.log("white")
                const data = {
                    whitemove: startpos + endpos
                }
                const formBody = Object.keys(data).map(key => encodeURIComponent(key) + '=' + encodeURIComponent(data[key])).join('&');
                fetch("http://" + window.location.host + "/api.php", {
                    method: 'POST',
                    body: formBody,
                    headers: { "Content-type": "application/x-www-form-urlencoded" }
                })
                    .then(response => console.log(response.json()))
                    .catch(err => console.log(err));
            } else if (start[startpos][0] == 'b') {
                console.log("black")
                const data = {
                    blackmove: startpos + endpos
                }
                const formBody = Object.keys(data).map(key => encodeURIComponent(key) + '=' + encodeURIComponent(data[key])).join('&');
                fetch("http://" + window.location.host + "/api.php", {
                    method: 'POST',
                    body: formBody,
                    headers: { "Content-type": "application/x-www-form-urlencoded" }
                })
                    .then(response => console.log(response.status()))
                    .catch(err => console.log(err));
            }
            

        }

        var config = {
            draggable: true,
            dropOffBoard: 'snapback',
            position: 'start',
            onChange: postMove
        }
        var board = Chessboard('myBoard', config);
        setInterval(async () => {
            const status = document.getElementById("status");
                var Best;
                var White;
                var Black;
                fetch("http://" + window.location.host + "/bestmove").then(response => {
                        console.log(response.statusText);
                        return response.text();
                    })
                    .then(data => {console.log(data); Best = data
                        fetch("http://" + window.location.host + "/whitemove").then(response => {
                                console.log(response.statusText);
                                return response.text();
                            })
                            .then(data => {console.log(data); White = data
                                fetch("http://" + window.location.host + "/blackmove").then(response => {
                                        console.log(response.statusText);
                                        return response.text();
                                    })
                                    .then(data => {console.log(data); Black = data
                                        status.innerHTML = "\
                                        Best Move: " + Best + "<br>\
                                        White Move: " + White + "<br>\
                                        Black Move: " + Black
                                    });
                            });
                            
                    });
                }, 100);
        </script>
    <form method="post">
        Best move:
        <input type="text" name="bestmove">
        White move:
        <input type="text" name="whitemove">
        Black move:
        <input type="text" name="blackmove">
        <input type="submit">
    </form>
</body>

</html>