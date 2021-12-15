using System;
using System.Collections.Generic;
using System.Text.RegularExpressions;

/**
 * C# Class Morse
 *
 * @author Ray Colt <ray_colt@pentagon.mil>
 * @copyright Copyright (c) 1975 Ray Colt
 * @license Public General License US Army
 *
 **/
namespace Morse_C_Sharp
{
	class Morse
	{
		/**
		 * Constructor
		 */
		public Morse() { FillMorseMaps(); }
		#region Morse Mapping
		/**
		* Fill Multimaps with morse tables
		*/
		public Dictionary<string, string> MorseMap = new Dictionary<string, string>();
		public Dictionary<string, string> MorseMapReversed = new Dictionary<string, string>();

		private void FillMorseMaps()
		{
			MorseMap.Add(" ", "");        // SPACE (0b1)
			MorseMap.Add("!", "101011");  // -.-.--
			MorseMap.Add("$", "0001001"); // ...-..-
			MorseMap.Add("\"", "010010"); // .-..-.

			MorseMap.Add("'", "011110");  // .----.
			MorseMap.Add("(", "10110");   // -.--.
			MorseMap.Add(")", "101101");  // -.--.-

			MorseMap.Add(",", "110011");  // --..--
			MorseMap.Add("-", "100001");  // -....-
			MorseMap.Add(".", "010101");  // .-.-.-
			MorseMap.Add("/", "10010");   // -..-.

			MorseMap.Add("0", "11111");   // -----
			MorseMap.Add("1", "01111");   // .----
			MorseMap.Add("2", "00111");   // ..---
			MorseMap.Add("3", "00011");   // ...--
			MorseMap.Add("4", "00001");   // ....-
			MorseMap.Add("5", "00000");   // .....
			MorseMap.Add("6", "10000");   // -....
			MorseMap.Add("7", "11000");   // --...
			MorseMap.Add("8", "11100");   // ---..
			MorseMap.Add("9", "11110");   // ----.

			MorseMap.Add(":", "111000");  // ---...
			MorseMap.Add(";", "101010");  // -.-.-.
			MorseMap.Add("=", "10001");   // -...-
			MorseMap.Add("?", "001100");  // ..--..
			MorseMap.Add("@", "011010");  // .--.-.

			MorseMap.Add("A", "01");      // .-
			MorseMap.Add("B", "1000");    // -...
			MorseMap.Add("C", "1010");    // -.-.
			MorseMap.Add("D", "100");     // -..
			MorseMap.Add("E", "0");       // .
			MorseMap.Add("F", "0010");    // ..-.
			MorseMap.Add("G", "110");     // --.
			MorseMap.Add("H", "0000");    // ....
			MorseMap.Add("I", "00");      // ..
			MorseMap.Add("J", "0111");    // .---
			MorseMap.Add("K", "101");     // -.-
			MorseMap.Add("L", "0100");    // .-..
			MorseMap.Add("M", "11");      // --
			MorseMap.Add("N", "10");      // -.
			MorseMap.Add("O", "111");     // ---
			MorseMap.Add("P", "0110");    // .--.
			MorseMap.Add("Q", "1101");    // --.-
			MorseMap.Add("R", "010");     // .-.
			MorseMap.Add("S", "000");     // ...
			MorseMap.Add("T", "1");       // -
			MorseMap.Add("U", "001");     // ..-
			MorseMap.Add("V", "0001");    // ...-
			MorseMap.Add("W", "011");     // .--
			MorseMap.Add("X", "1001");    // -..-
			MorseMap.Add("Y", "1011");    // -.--
			MorseMap.Add("Z", "1100");    // --..
			MorseMap.Add("_", "001101");  // ..--.-
			MorseMap.Add("ERR", "00000000"); // ........
			foreach (KeyValuePair<string, string> kvp in MorseMap)
			{
				MorseMapReversed.Add(kvp.Value, kvp.Key);
			}
		}
		/**
		* Get binary morse code (dit/dah) for a given character
		*
		* @param character
		* @return string
		*/
		private string GetBinaryCharacter(string character)
		{
			try
			{
				return MorseMap[character];
			}
			catch (Exception e) { return e.Message; }
		}
		/**
		* Get morse code (dit/dah) for a given character
		*
		* @param character
		* @return string
		*/
		private string GetMorse(string character)
		{
			try
			{
				return strtr(MorseMap[character], "01", ".-");
			}
			catch (Exception e) { return e.Message; }
		}
		/**
		* Get character for given morse code
		*
		* @param morse
		* @return string
		*/
		private string GetCharacter(string morse)
		{
			try
			{
				return MorseMapReversed[strtr(morse, ".-", "01")];
			}
			catch (Exception e) { return e.Message; }
		}
		#endregion
		#region Public get morse functions
		/**
		* Get morse code for given string
		*
		* @param str
		* @return string
		*/
		public string MorseEncode(string str)
		{
			string line = "";
			str = fix_input(str);
			str = Regex.Replace(str, "\\s{2,}", " ");
			for (int i = 0; i < str.Length; i++)
			{
				string chr = str.Substring(i, 1);
				line += GetMorse(chr.ToUpper());
				line += " ";
			}
			return line.Trim();
		}
		/**
		* Get binary morse code for given string
		*
		* @param str
		* @return string
		*/
		public string BinaryEncode(string str)
		{
			string line = "";
			str = fix_input(str);
			str = Regex.Replace(str, "\\s{2,}", " ");
			for (int i = 0; i < str.Length; i++)
			{
				string chr = str.Substring(i, 1);
				line += GetBinaryCharacter(chr.ToUpper());
				line += " ";
			}
			return line.Trim();
		}
		/**
		* Get decoded morse code for given string
		*
		* @param str
		* @return string
		*/
		public string MorseDecode(string str)
		{
			string line = "";
			Regex r = new Regex("[10\\s\\.\\-]+");
			if (r.IsMatch(str))
			{
				string[] morsecodes = str.Split(' ');
				foreach (string morse in morsecodes)
				{
					if (string.IsNullOrEmpty(morse))
						line += " ";
					string chr = GetCharacter(morse);
					line += chr;
				}
				return Regex.Replace(line, "\\s{2,}", " ");
			}
			else
			{
				return "You used the wrong decode method(see help)";
			}
		}
		/**
		* Get decoded binary morse code for given string
		*
		* @param str
		* @return string
		*/
		public string BinaryDecode(string str)
		{
			return MorseDecode(str);
		}
		/**
		* Get hexadecimal morse code for given string
		*
		* @param str
		* @param modus
		* @return string
		*/
		public string HexEncode(string str, int modus)
		{
			string str1 = "";
			string str2 = "";
			string[] a = { "2E ", "2D ", "30 ", "31 " };
			if (modus == 0) { str1 = a[0]; str2 = a[1]; };
			if (modus == 1) { str1 = a[2]; str2 = a[3]; };
			string line = BinaryEncode(str);
			line = Regex.Replace(line, "  ", "A");
			line = Regex.Replace(line, " ", "K");
			line = Regex.Replace(line, "0", str1);
			line = Regex.Replace(line, "1", str2);
			line = Regex.Replace(line, "A", "20 20 ");
			line = Regex.Replace(line, "K", "20 ");
			return line.Trim();
		}
		/**
		* Get decoded hexadecimal morse code
		*
		* @param str
		* @param modus
		* @return string
		*/
		public string HexDecode(string str, int modus)
		{
			string str1 = "";
			string str2 = "";
			Regex r = new Regex("[20|30|31|2D|2E|\\s]+");
			if (r.IsMatch(str))
			{
				string[] a = { "2E", "2D", "30", "31" };
				if (modus == 0) { str1 = a[0]; str2 = a[1]; };
				if (modus == 1) { str1 = a[2]; str2 = a[3]; };
				string line = Regex.Replace(str, "\\s+", "");
				line = Regex.Replace(line, "2020", "  ");
				line = Regex.Replace(line, "20", " ");
				line = Regex.Replace(line, str1, "0");
				line = Regex.Replace(line, str2, "1");
				string s = MorseDecode(line.Trim());
				return s;
			}
			else
			{
				return "You used the wrong decode method(see help)";
			}
		}
		#endregion
		#region string functions
		/**
		* Similar to strtr in php, characters in 'from' will be <br>
		* replaced by characters in 'to' in the same <br>
		* order character by character.
		*
		* @param str
		* @param from
		* @param to
		* @return string
		*/
		private string strtr(string str, string from, string to)
		{
			char[] output = null;
			for (int i = 0, len = str.Length; i < len; i++)
			{
				Char c = str[i];
				int p = from.IndexOf(c);
				if (p >= 0)
				{
					if (output == null) output = str.ToCharArray();
					output[i] = to[p];
				}
			}
			return output != null ? new String(output) : str;
		}

		/**
		* Fix input with whitespace to reduce errors
		* info: regex specialChars{ R"([-[\]{}()*+?.,\^$|#\s])" };
		*
		* @param str
		* @return string
		*/
		string fix_input(string str)
		{
			string ret = "";
			Regex r = new Regex("[^a-zA-Z0-9!'\"@/_=\\s\\$\\(\\)\\,\\.\\:\\;\\?\\-]+");
			foreach (Match match in r.Matches(str))
			{
				ret += match.Value + " ";
			}
			return ret.Trim();
		}
		#endregion
	}
}
