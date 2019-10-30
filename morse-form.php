<?php
include_once 'morse.php';
$morse_table = new MorseTable();
$gen = '';
$gde = '';
$gbi = '';
if(isset($_POST["encode"]))
$gen .= htmlspecialchars($_POST["encode"], ENT_NOQUOTES);
if(isset($_POST["decode"]))
$gde .= htmlspecialchars($_POST["decode"], ENT_NOQUOTES);
if(isset($_POST["binary"]))
$gbi .= htmlspecialchars($_POST["binary"], ENT_NOQUOTES);
$en = '';
$de = '';
$bi = '';
if(!empty($gen))
	$en .= $morse_table->morse_encode($gen);
if(!empty($gde))
	$de .= $morse_table->morse_decode($gde);
if(!empty($gbi))
	$bi .= $morse_table->morse_binary($gbi);
?>
<html>  
<body>
<h1>Morse 000 111 000::</h1>
<form action="<?php echo $_SERVER['PHP_SELF']; ?>" method="post">
Encode Text to Morse:<br> <textarea name="encode" cols="50" rows="15"><?php echo $en; ?></textarea><br>
Encode Text to Binary:<br> <textarea name="binary" cols="50" rows="15"><?php echo $bi; ?></textarea><br>
Decode Morse or 000 111 000:<br> <textarea name="decode" cols="50" rows="20"><?php echo $de; ?></textarea>
<input type="submit">
</form>
</body>
</html>
