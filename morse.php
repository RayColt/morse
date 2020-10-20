<?php
/**
 * PHP Class MorseTable
 *
 * @author Ray Colt <ray_colt@pentagon.mil>
 * @copyright Copyright (c) 1975 Ray Colt
 * @license Public General License US Army
 *
 */

class MorseTable {
    /**
     * A reverse copy of the table (morse => character)
     *
     * @var array
     */
    private $reversedTable;

    /**
     * A table of predefined morse code mappings
     *
     * @var array
     */
    private $morse_table = [
        ' ' => '', // SPACE (0b1)
        '!' => '101011',    // -.-.--
        '"' => '010010',    // .-..-.
        '$' => '0001001',   // ...-..-
		
        //'&' => '01000',
        "'" => '011110',    // .----.
        '(' => '10110',     // -.--.
        ')' => '101101',    // -.--.-
        
        //'+' => '01010',					
        ',' => '110011',    // --..--
        '-' => '100001',    // -....-
        '.' => '010101',    // .-.-.-
        '/' => '10010',     // -..-.
		
        '0' => '11111',     // -----
        '1' => '01111',     // .----
        '2' => '00111',     // ..---
        '3' => '00011',     // ...--
        '4' => '00001',     // ....-
        '5' => '00000',     // .....
        '6' => '10000',     // -....
        '7' => '11000',     // --...
        '8' => '11100',     // ---..
        '9' => '11110',     // ----.
		
        ':' => '111000',    // ---...
        ';' => '101010',    // -.-.-.		
        '=' => '10001',     // -...-
        '?' => '001100',    // ..--..
        '@' => '011010',    // .--.-.
		
        'A' => '01',        // .-
        'B' => '1000',      // -...
        'C' => '1010',      // -.-.
        'D' => '100',       // -..
        'E' => '0',         // .
        'F' => '0010',      // ..-.
        'G' => '110',       // --.
        'H' => '0000',      // ....
        'I' => '00',        // ..
        'J' => '0111',      // .---
        'K' => '101',       // -.-
        'L' => '0100',      // .-..
        'M' => '11',        // --
        'N' => '10',        // -.
        'O' => '111',       // ---
        'P' => '0110',      // .--.
        'Q' => '1101',      // --.-
        'R' => '010',       // .-.
        'S' => '000',       // ...
        'T' => '1',         // -
        'U' => '001',       // ..-
        'V' => '0001',      // ...-
        'W' => '011',       // .--
        'X' => '1001',      // -..-
        'Y' => '1011',      // -.--
        'Z' => '1100',      // --..        
        '_' => '001101',    // ..--.-
        'ERR' => '00000000' // ........
        ];

    /**
     * Constructs a new instance of the table
     */
    public function __construct() {
        $this->reversedTable = array_flip($this->morse_table);
    }

    /**
     * Get binary morse code (dit/dah) for a given character
     *
     * @param  string $character
     * @return string
     */
    public function getBinChar($character) { 
        $key = $this->morse_table[$character];
        return isset($key) ? $key : false;
    }

    /**
     * Get morse code (dit/dah) for a given character
     *
     * @param  string $character
     * @return string
     */
    public function getMorse($character) { 
        $key = strtr($this->morse_table[$character], '01', '.-');
        return isset($key) ? $key : false;
    }

    /**
     * Get character for given morse code
     *
     * @param  string $morse
     * @return string
     */
    public function getCharacter($morse) {
        $key = strtr($morse, '.-', '01');
        return isset($this->reversedTable[$key]) ? $this->reversedTable[$key] : false;
    }

    /**
     * Get binary morse code for given string
     *
     * @param  string $string
     * @return string
     */
    public function morse_binary($string) {
        $line = '';
        for ($i=0;$i<strlen($string);$i++) {
            $char = substr($string,$i,1);
            $line .= $this->getBinChar(strtoupper($char));
            $line .= ' ';
        }
        return trim($line);
    }

    /**
     * Get morse code for given string
     *
     * @param  string $string
     * @return string
     */
    public function morse_encode($string) {
        $line = '';
        for ($i=0;$i<strlen($string);$i++) {
            $char = substr($string,$i,1);
            $line .= $this->getMorse(strtoupper($char));
            $line .= ' ';
        }
        return trim($line);
    }

    /**
     * Get character string for given morse code
     *
     * @param  string $string
     * @return string
     */    
    public function morse_decode($string) {
        $line = '';
        $morsecodes = array();
        $morsecodes = explode(' ',$string);
        foreach ($morsecodes as $morse) {
            if (array_key_exists(null, $morsecodes) && empty($morse))
                $line .= ' ';
            $character = $this->getCharacter($morse);
            $line .= $character;
         }
         return trim(preg_replace('/\s+/', ' ', $line));
     }
}
// initialize the above class
$morse_table = new MorseTable();
$gen = '';
$gde = '';
$gbi = '';
if(isset($_GET["encode"]))
$gen .= htmlspecialchars($_GET["encode"], ENT_NOQUOTES);
if(isset($_GET["decode"]))
$gde .= htmlspecialchars($_GET["decode"], ENT_NOQUOTES);
if(isset($_GET["binary"]))
$gbi .= htmlspecialchars($_GET["binary"], ENT_NOQUOTES);
$en = '';
$de = '';
$bi = '';
if(!empty($gen))
	$en .= $morse_table->morse_encode($gen);
if(!empty($gde))
	$de .= $morse_table->morse_decode($gde);
if(!empty($gbi))
	$bi .= $morse_table->morse_binary($gbi);	
echo $en;
echo $de;
echo $bi;
?>
