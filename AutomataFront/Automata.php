<?php
/**
 * Project: Automata
 * File: Automata.php
 * Author: Jeff Watson
 * Date: 2/13/14
 * Time: 11:46 AM
 */

?>

<!DOCTYPE html>
<html>
<head>
    <meta charset="UTF-8">
    <title>Automata</title>

    <!-- css -->
    <link rel="stylesheet" href="css/main.css"/>

    <!-- Bootstrap -->
    <link rel="stylesheet" href="css/bootstrap.min.css"/>
    <script type="text/javascript" src="js/bootstrap.min.js"></script>

    <!-- jQuery -->
    <script type="text/javascript" src="js/jQuery-v2-0-3.js"></script>

    <!-- js -->
    <script type="text/javascript" src="js/main.js"></script>

</head>
<body>
    <div class="container">
        <h1>Automata Creator</h1>
        <h3>Enter a Regular Expression and click Go!</h3>

        <?php
            include("php/components/rules.php");
            include("php/components/form.php");
            include("php/components/pic_area.php");
        ?>

        <div id="pdf_div"></div>

    </div>

</body>
</html>