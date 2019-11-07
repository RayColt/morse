# Colt's Morse PHP, Java and JavaScript
A PHP&JAVA servlet with a binary Morse mapping, inverted(think Endian/IBM PowerPC) based upon this c code* of my kids and me, inventors of Morse, it became the (international) USA morse code! **based upon Synthesizer Binary tables(speach)...or just a military algorithm:-). <br><br>Public General License US Army means free of use, public that is. <br> Prof. and GA Ray Colt, USA Hartford. <br><BR>REMOVE THE FIRST BIT, REVERSE THE BINARY VALUES, ET VOILA THE MORSE CODE!<BR>
<a href="https://raycolt.github.io/morse/">WORKING EXAMPLE</a><br>
uint16_t Morse::encode(uint8_t character) {<br>
  switch (character) {<br>
    
    case 32: return 0b1;          // SPACE
    case 33: return 0b1110101;    // !
    case 34: return 0b1010010;    // "
    case 36: return 0b11001000;   // $

    case 38: return 0b100010;     // &
    case 39: return 0b1011110;    // '
    case 40: return 0b101101;     // (
    case 41: return 0b1101101;    // )

    case 43: return 0b101010;     // +
    case 44: return 0b1110011;    // ,
    case 45: return 0b1100001;    // -
    case 46: return 0b1101010;    // .
    case 47: return 0b101001;     // /

    case 48: return 0b111111;     // 0
    case 49: return 0b111110;     // 1
    case 50: return 0b111100;     // 2
    case 51: return 0b111000;     // 3
    case 52: return 0b110000;     // 4
    case 53: return 0b100000;     // 5
    case 54: return 0b100001;     // 6
    case 55: return 0b100011;     // 7
    case 56: return 0b100111;     // 8
    case 57: return 0b101111;     // 9

    case 58: return 0b1000111;    // :
    case 59: return 0b1010101;    // ;

    case 61: return 0b110001;     // =

    case 63: return 0b1001100;    // ?
    case 64: return 0b1010110;    // @

    case 65: return 0b110;        // A
    case 66: return 0b10001;      // B
    case 67: return 0b10101;      // C
    case 68: return 0b1001;       // D
    case 69: return 0b10;         // E
    case 70: return 0b10100;      // F
    case 71: return 0b1011;       // G
    case 72: return 0b10000;      // H
    case 73: return 0b100;        // I
    case 74: return 0b11110;      // J
    case 75: return 0b1101;       // K
    case 76: return 0b10010;      // L
    case 77: return 0b111;        // M
    case 78: return 0b101;        // N
    case 79: return 0b1111;       // O
    case 80: return 0b10110;      // P
    case 81: return 0b11011;      // Q
    case 82: return 0b1010;       // R
    case 83: return 0b1000;       // S
    case 84: return 0b11;         // T
    case 85: return 0b1100;       // U
    case 86: return 0b11000;      // V
    case 87: return 0b1110;       // W
    case 88: return 0b11001;      // X
    case 89: return 0b11101;      // Y
    case 90: return 0b10011;      // Z
    case 95: return 0b1101100;    // _
    default: return 0b100000000;  // INVALID
  }
}
<script type="text/javascript">	
/**
 * JavaScript MorseMap
 *
 * @author Ray Colt <ray_colt@pentagon.mil>
 * @copyright Copyright (c) 2015 Ray Colt
 * @license Public General License US Army
 *
 * For Lauren 13-09-2019.
 */ 
	var morseMap = {
		" " : "", // SPACE (0b1)
		"!" : "101011", // -.-.--
		"\"" : "010010", // .-..-.
		"$" : "0001001", // ...-..-
		"'" : "011110", // .----.
		"(" : "10110", // -.--.
		")" : "101101", // -.--.-
		"," : "110011", // --..--
		"-" : "100001", // -....-
		"." : "010101", // .-.-.-
		"/" : "10010", // -..-.
		"0" : "11111", // -----
		"1" : "01111", // .----
		"2" : "00111", // ..---
		"3" : "00011", // ...--
		"4" : "00001", // ....-
		"5" : "00000", // .....
		"6" : "10000", // -....
		"7" : "11000", // --...
		"8" : "11100", // ---..
		"9" : "11110", // ----.
		":" : "111000", // ---...
		";" : "101010", // -.-.-.
		"=" : "10001", // -...-
		"?" : "001100", // ..--..
		"@" : "011010", // .--.-.
		"A" : "01", // .-
		"B" : "1000", // -...
		"C" : "1010", // -.-.
		"D" : "100", // -..
		"E" : "0", // .
		"F" : "0010", // ..-.
		"G" : "110", // --.
		"H" : "0000", // ....
		"I" : "00", // ..
		"J" : "0111", // .---
		"K" : "101", // -.-
		"L" : "0100", // .-..
		"M" : "11", // --
		"N" : "10", // -.
		"O" : "111", // ---
		"P" : "0110", // .--.
		"Q" : "1101", // --.-
		"R" : "010", // .-.
		"S" : "000", // ...
		"T" : "1", // -
		"U" : "001", // ..-
		"V" : "0001", // ...-
		"W" : "011", // .--
		"X" : "1001", // -..-
		"Y" : "1011", // -.--
		"Z" : "1100", // --..
		"_" : "001101", // ..--.-
		"ERR" : "00000000" // ........
	};
	var reversedMorseMap = array_flip(morseMap);
	
	/**
	 * Similar to array_flip in php, returns an array in flip order, <br>
	 * i.e. keys from array become values and values from array become keys. <br>
     *
	 * @param arr
	 * @return array
	 */		
	function array_flip(arr) {
		var key = null;
		var tmp_arr = {};
		for (key in arr) {
			if (arr.hasOwnProperty(key))
				tmp_arr[arr[key]] = key;
		}
		return tmp_arr;
	}
		
	/**
	 * Similar to strtr in php, characters in 'from' will be <br>
	 * replaced by characters in 'to' in the same <br>
	 * order character by character.
	 * 
	 * @param str
	 * @param from
	 * @param to
	 * @return String
	 */
	function strtr(str, from, to) {
		var out = null;
		var len = 0;
		for (var i = 0, len = str.length; i < len; i++) {
			var c = str.charAt(i);
			var p = from.indexOf(c);
			if (p >= 0) {				
				if (out == null)
					out = str.split("");
				out[i] = to.charAt(p);
			}
		}
		return out != null ? out.join("") : str;
	}
	/**
	 * Get binary morse code (dit/dah) for a given character
	 *
	 * @param character
	 * @return String
	 */
	function getBinChar(character) {
		return morseMap[character];
	}
	/**
	 * Get morse code (dit/dah) for a given character
	 *
	 * @param character
	 * @return String
	 */
	function getMorse(character) {
		return strtr(morseMap[character], "01", ".-");
	}
	/**
	 * Get character for given morse code
	 *
	 * @param morse
	 * @return String
	 */
	function getCharacter(morse) {
		return reversedMorseMap[strtr(morse, ".-", "01")];
	}
	/**
	 * Get binary morse code for given string
	 *
	 * @param str
	 * @return String
	 */
	function morse_binary(str) {
		var line = "";
		for (var i = 0; i < str.length; i++) {
			var chr = str.substring(i, i + 1);
			line += getBinChar(chr.toUpperCase());
			line += " ";
		}
		return line.trim();
	}
	/**
	 * Get morse code for given string
	 *
	 * @param str
	 * @return String
	 */
	function morse_encode(str) {
		var line = "";
		for (var i = 0; i < str.length; i++) {
			var chr = str.substring(i, i + 1);
			line += getMorse(chr.toUpperCase());
			line += " ";
		}
		return line.trim();
	}
	/**
	 * Get character string for given morse code
	 *
	 * @param str
	 * @return String
	 */
	function morse_decode(str) {
		var line = "";
		var morse = null;
		var morsecodes = str.split(" ");
		for (morse in morsecodes) {
			if (!morsecodes.hasOwnProperty(morse))
				line += " ";
			var chr = getCharacter(morsecodes[morse]);
			line += chr;
		}
		return line.replace(/\s{2,}/g," ").trim();
	}
</script>

<script type="text/javascript">	
	function morseForm() {
	  var modus = document.querySelector('input[name="modus"]:checked').value;
	  var data =  document.getElementById("data").value;
	  if(modus == "encode")
		  document.getElementById("data").value = morse_encode(data);
	  if(modus == "decode")
		  document.getElementById("data").value = morse_decode(data);	  
	  if(modus == "binary_encode")
		  document.getElementById("data").value = morse_binary(data);	  
	}		
</script>
<table width="100%" border="0" cellspacing="2" cellpadding="2">
<tr>
  <td align="center"><b>Morse</b></td>
</tr>
<tr>
  <td align="center"><textarea id="data" name="data" cols="50" rows="15">ABC DEFGHIJKLMNOPQRSTUVWXYZ 12 34567890 !$'(),-./ :; =?@"</textarea></td>
</tr>
<tr>
  <td align="center"><table width="333" border="0">
      <tr>
        <td align="center"><label>
            <input type="radio" id="modus" name="modus" value="encode" checked="checked"/>
            Encode</label></td>
        <td align="center"><label>
            <input type="radio" id="modus" name="modus" value="decode" />
            Decode</label></td>
        <td align="center"><label>
            <input type="radio" id="modus" name="modus" value="binary_encode" />
            Binary Encode</label></td>
      </tr>
    </table></td>
</tr>
<tr>
  <td align="center"><input type="submit" onClick="morseForm()" /></td>
</tr>
</table>
