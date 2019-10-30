package morsepack;
import java.util.HashMap;
import java.util.Map;
import java.util.Map.Entry;
import java.util.stream.Collectors;

/**
 * JAVA Class MorseTable
 *
 * @author Ray Colt <ray_colt@pentagon.mil>
 * @copyright Copyright (c) 1975 Ray Colt
 * @license Public General License US Army
 *
 * @see For Lauren 13-09-2019.
 *
 **/
public class Morse {

	HashMap<String, String> reversedTable = new HashMap<String, String>();
	/**
	 * The Morse Mapping
	 */
	private static Map<String, String> morseMap = new HashMap<String, String>() {
		private static final long serialVersionUID = 1L;
		{
			put(" ", ""); // SPACE (0b1)
			put("!", "101011"); // -.-.--
			put("\"", "010010"); // .-..-.
			put("$", "0001001"); // ...-..-

			put("'", "011110"); // .----.
			put("(", "10110"); // -.--.
			put(")", "101101"); // -.--.-

			put(",", "110011"); // --..--
			put("-", "100001"); // -....-
			put(".", "010101"); // .-.-.-
			put("/", "10010"); // -..-.

			put("0", "11111"); // -----
			put("1", "01111"); // .----
			put("2", "00111"); // ..---
			put("3", "00011"); // ...--
			put("4", "00001"); // ....-
			put("5", "00000"); // .....
			put("6", "10000"); // -....
			put("7", "11000"); // --...
			put("8", "11100"); // ---..
			put("9", "11110"); // ----.

			put(":", "111000"); // ---...
			put(";", "101010"); // -.-.-.
			put("=", "10001"); // -...-
			put("?", "001100"); // ..--..
			put("@", "011010"); // .--.-.

			put("A", "01"); // .-
			put("B", "1000"); // -...
			put("C", "1010"); // -.-.
			put("D", "100"); // -..
			put("E", "0"); // .
			put("F", "0010"); // ..-.
			put("G", "110"); // --.
			put("H", "0000"); // ....
			put("I", "00"); // ..
			put("J", "0111"); // .---
			put("K", "101"); // -.-
			put("L", "0100"); // .-..
			put("M", "11"); // --
			put("N", "10"); // -.
			put("O", "111"); // ---
			put("P", "0110"); // .--.
			put("Q", "1101"); // --.-
			put("R", "010"); // .-.
			put("S", "000"); // ...
			put("T", "1"); // -
			put("U", "001"); // ..-
			put("V", "0001"); // ...-
			put("W", "011"); // .--
			put("X", "1001"); // -..-
			put("Y", "1011"); // -.--
			put("Z", "1100"); // --..
			put("_", "001101"); // ..--.-
			put("ERR", "00000000"); // ........
		}
	};

	/**
	 * Constructor
	 */
	public Morse() {
		reversedTable = (HashMap<String, String>) invert(morseMap);
	}

	/**
	 * Invert Map
	 * 
	 * @param map
	 * @return Map
	 */
	public static <V, K> Map<V, K> invert(Map<K, V> map) {
		return map.entrySet().stream().collect(Collectors.toMap(Entry::getValue, Entry::getKey));
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
	public String strtr(String str, String from, String to) {
		char[] out = null;
		for (int i = 0, len = str.length(); i < len; i++) {
			char c = str.charAt(i);
			int p = from.indexOf(c);
			if (p >= 0) {
				if (out == null)
					out = str.toCharArray();
				out[i] = to.charAt(p);
			}
		}
		return out != null ? new String(out) : str;
	}

	/**
	 * Checks whether a string is empty.
	 *
	 * @param s
	 * @return boolean
	 */
	public boolean isEmpty(String s) {
		if (s != null && s.trim().length() > 0) {
			return false;
		} else {
			return true;
		}
	}

	/**
	 * Get binary morse code (dit/dah) for a given character
	 *
	 * @param character
	 * @return String
	 */
	public String getBinChar(String character) {
		return morseMap.get(character);
	}

	/**
	 * Get morse code (dit/dah) for a given character
	 *
	 * @param character
	 * @return String
	 */
	public String getMorse(String character) {
		return strtr(morseMap.get(character), "01", ".-");
	}

	/**
	 * Get character for given morse code
	 *
	 * @param morse
	 * @return String
	 */
	public String getCharacter(String morse) {
		return reversedTable.get(strtr(morse, ".-", "01"));
	}

	/**
	 * Get binary morse code for given string
	 *
	 * @param str
	 * @return String
	 */
	public String morse_binary(String str) {
		String line = "";
		for (int i = 0; i < str.length(); i++) {
			String chr = str.substring(i, i + 1);
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
	public String morse_encode(String str) {
		String line = "";
		for (int i = 0; i < str.length(); i++) {
			String chr = str.substring(i, i + 1);
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
	public String morse_decode(String str) {
		String line = "";
		String[] morsecodes = str.split(" ");
		for (String morse : morsecodes) {
			if (isEmpty(morse))
				line += " ";
			String chr = getCharacter(morse);
			line += chr;
		}
		return line.replaceAll("\\s{2,}", " ").trim();
	}

	/**
	 * Main function
	 * 
	 * @param args
	 */
	public static void main(String[] args) {
		Morse morse = new Morse();
		String str = "Howdy \"Ray\" Colt!";
		System.out.println(morse.morse_encode(str));
		String mrs = ".... --- .-- -.. -.--  .-..-. .-. .- -.-- .-..-.  -.-. --- .-.. - -.-.--";
		System.out.println(morse.morse_decode(mrs));
		System.out.println(morse.morse_binary(str));
	}
}
