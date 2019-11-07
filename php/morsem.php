<?php
/* a small/mobile form example */
include_once 'morse.php';
$morse_table = new MorseTable();
$data = '';
$modus = '';
$d = '';
if(isset($_GET["modus"]))
$modus .= htmlspecialchars($_GET["modus"], ENT_NOQUOTES);
if(isset($_GET["data"]))
$data .= htmlspecialchars($_GET["data"], ENT_NOQUOTES);
if($modus == 'encode')
	$d .= $morse_table->morse_encode($data);
if($modus == 'decode')
	$d .= $morse_table->morse_decode($data);
if($modus == 'binary_encode')
	$d .= $morse_table->morse_binary($data);
?>
<html>  
<body>
<form action="<?php echo $_SERVER['PHP_SELF']; ?>" method="get">
  <table width="100%" border="0" cellspacing="2" cellpadding="2">
    <tr>
      <td align="center"><b>Morse</b></td>
    </tr>
    <tr>
      <td align="center"><textarea name="data" cols="50" rows="15"><?php echo $d; ?></textarea></td>
    </tr>
    <tr>
      <td align="center"><table width="333">
          <tr>
            <td align="center"><label>
                <input type="radio" name="modus" value="encode" checked="checked"/>
                Encode</label></td>
            <td align="center"><label>
                <input type="radio" name="modus" value="decode" />
                Decode</label></td>
            <td align="center"><label>
                <input type="radio" name="modus" value="binary_encode" />
                Binary Encode</label></td>
          </tr>
        </table></td>
    </tr>
    <tr>
      <td align="center"><input type="submit" /></td>
    </tr>
  </table>
</form>
</body>
</html>
