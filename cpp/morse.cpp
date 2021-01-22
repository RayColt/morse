#include <string>
#include <iostream>
#include <map>
#include <iterator>
#include <vector>
#include <regex>
#include <windows.h>

using namespace std;
/**
* C++ Morse
*
* @author Ray Colt <ray_colt@pentagon.mil>
* @copyright Copyright (c) 1975, 2021 Ray Colt
* @license Public General License US Army, Microsoft Corporation (MIT)
*
* Derived from ARPANET Pentagon's morse, the url more save, http version.
* Feel free to make morse, morsed or morseb binaries
* for it, like once was implemented into Linux and Unix os's.
*
* Usage console app version: ./morse.exe
* Usage console line two arguments version: ./morse.exe "[e,b,d]" "morse or txt"
* e=encode, b=binary-encode, d=decode
* ./morse.exe e "morse is fun!!" OR ./morse.exe "e" "morse is fun!!"
**/
class Morse
{
public:
	Morse() { fill_morse_maps(); }

private:
	multimap <string, string> morse_map;
	multimap <string, string> morse_map_reversed;
	void fill_morse_maps()
	{
		morse_map.insert(pair <string, string>(" ", ""));        // SPACE (0b1)
		morse_map.insert(pair <string, string>("!", "101011"));  // -.-.--
		morse_map.insert(pair <string, string>("$", "0001001")); // ...-..-
		morse_map.insert(pair <string, string>("\"", "010010")); // .-..-.

		morse_map.insert(pair <string, string>("'", "011110"));  // .----.
		morse_map.insert(pair <string, string>("(", "10110"));   // -.--.
		morse_map.insert(pair <string, string>(")", "101101"));  // -.--.-

		morse_map.insert(pair <string, string>(",", "110011"));  // --..--
		morse_map.insert(pair <string, string>("-", "100001"));  // -....-
		morse_map.insert(pair <string, string>(".", "010101"));  // .-.-.-
		morse_map.insert(pair <string, string>("/", "10010"));   // -..-.

		morse_map.insert(pair <string, string>("0", "11111"));   // -----
		morse_map.insert(pair <string, string>("1", "01111"));   // .----
		morse_map.insert(pair <string, string>("2", "00111"));   // ..---
		morse_map.insert(pair <string, string>("3", "00011"));   // ...--
		morse_map.insert(pair <string, string>("4", "00001"));   // ....-
		morse_map.insert(pair <string, string>("5", "00000"));   // .....
		morse_map.insert(pair <string, string>("6", "10000"));   // -....
		morse_map.insert(pair <string, string>("7", "11000"));   // --...
		morse_map.insert(pair <string, string>("8", "11100"));   // ---..
		morse_map.insert(pair <string, string>("9", "11110"));   // ----.

		morse_map.insert(pair <string, string>(":", "111000"));  // ---...
		morse_map.insert(pair <string, string>(";", "101010"));  // -.-.-.
		morse_map.insert(pair <string, string>("=", "10001"));   // -...-
		morse_map.insert(pair <string, string>("?", "001100"));  // ..--..
		morse_map.insert(pair <string, string>("@", "011010"));  // .--.-.

		morse_map.insert(pair <string, string>("A", "01"));      // .-
		morse_map.insert(pair <string, string>("B", "1000"));    // -...
		morse_map.insert(pair <string, string>("C", "1010"));    // -.-.
		morse_map.insert(pair <string, string>("D", "100"));     // -..
		morse_map.insert(pair <string, string>("E", "0"));       // .
		morse_map.insert(pair <string, string>("F", "0010"));    // ..-.
		morse_map.insert(pair <string, string>("G", "110"));     // --.
		morse_map.insert(pair <string, string>("H", "0000"));    // ....
		morse_map.insert(pair <string, string>("I", "00"));      // ..
		morse_map.insert(pair <string, string>("J", "0111"));    // .---
		morse_map.insert(pair <string, string>("K", "101"));     // -.-
		morse_map.insert(pair <string, string>("L", "0100"));    // .-..
		morse_map.insert(pair <string, string>("M", "11"));      // --
		morse_map.insert(pair <string, string>("N", "10"));      // -.
		morse_map.insert(pair <string, string>("O", "111"));     // ---
		morse_map.insert(pair <string, string>("P", "0110"));    // .--.
		morse_map.insert(pair <string, string>("Q", "1101"));    // --.-
		morse_map.insert(pair <string, string>("R", "010"));     // .-.
		morse_map.insert(pair <string, string>("S", "000"));     // ...
		morse_map.insert(pair <string, string>("T", "1"));       // -
		morse_map.insert(pair <string, string>("U", "001"));     // ..-
		morse_map.insert(pair <string, string>("V", "0001"));    // ...-
		morse_map.insert(pair <string, string>("W", "011"));     // .--
		morse_map.insert(pair <string, string>("X", "1001"));    // -..-
		morse_map.insert(pair <string, string>("Y", "1011"));    // -.--
		morse_map.insert(pair <string, string>("Z", "1100"));    // --..
		morse_map.insert(pair <string, string>("_", "001101"));  // ..--.-
		morse_map.insert(pair <string, string>("ERR", "00000000")); // ........
		// invert morse_map
		for (const auto& it : morse_map)
		{
			morse_map_reversed.insert(make_pair(it.second, it.first));
		}
	}

private:
	/**
	* Get binary morse code (dit/dah) for a given character
	*
	* @param character
	* @return string
	*/
	string getBinChar(string character)
	{
		return  morse_map.find(character)->second;
	}

private:
	/**
	* Get morse code (dit/dah) for a given character
	*
	* @param character
	* @return string
	*/
	string getMorse(string character)
	{
		return strtr(morse_map.find(character)->second, "01", ".-");
	}

private:
	/**
	* Get character for given morse code
	*
	* @param morse
	* @return string
	*/
	string getCharacter(string morse)
	{
		return morse_map_reversed.find(strtr(morse, ".-", "01"))->second;
	}

public:
	/**
	* Get binary morse code for given string
	*
	* @param str
	* @return string
	*/
	string morse_binary(string str)
	{
		string line = "";
		for (size_t i = 0; i < str.length(); i++)
		{
			string chr = str.substr(i, 1);
			line += getBinChar(stringToUpper(chr));
			line += " ";
		}
		return trim(line);
	}

public:
	/**
	* Get morse code for given string
	*
	* @param str
	* @return string
	*/
	string morse_encode(string str)
	{
		string line = "";
		for (size_t i = 0; i < str.length(); i++)
		{
			string chr = str.substr(i, 1);
			line += getMorse(stringToUpper(chr));
			line += " ";
		}
		return trim(line);
	}

public:
	/**
	* Get character string for given morse code
	*
	* @param str
	* @return string
	*/
	string morse_decode(string str)
	{
		string line = "";
		regex e("[10\\s\\.\\-]+");
		if (regex_match(str, e))
		{
			vector<string> morsecodes = explode(str, ' ');
			for (auto morse : morsecodes)
			{
				if (morse.empty())
					line += " ";
				string chr = getCharacter(morse);
				line += chr;
			}
			regex e("\\s{2,}");
			return regex_replace(line, e, " ");
		}
		else
		{
			return "only these characters in morse are allowed: 0 1 . - and spaces";
		}
	}

public:
	/**
	* (\  /)
	* ( .  .)
	* Get hexadecimal morse code for given string
	*
	* @param str
	* @param modus
	* @return string
	*/
	string bin_morse_hexadecimal(string str, int modus)
	{
		string str1, str2;
		const char* a[] = { "2E ", "2D ", "30 ", "31 " };
		if (modus == 0) { str1 = a[0]; str2 = a[1]; };
		if (modus == 1) { str1 = a[2]; str2 = a[3]; };
		string line = morse_binary(str);
		line = regex_replace(line, regex("  "), "A");
		line = regex_replace(line, regex(" "), "K");
		line = regex_replace(line, regex("0"), str1);
		line = regex_replace(line, regex("1"), str2);
		line = regex_replace(line, regex("A"), "20 20 ");
		line = regex_replace(line, regex("K"), "20 ");
		return trim(line);
	}

public:
	/**
	* (\  /)
	* ( .  .)
	* Get txt for given hexadecimal morse code
	*
	* @param str
	* @param modus
	* @return string
	*/
	string hexadecimal_bin_txt(string str, int modus)
	{
		string str1, str2;
		const char* a[] = { "2E", "2D", "30", "31" };
		if (modus == 0) { str1 = a[0]; str2 = a[1]; };
		if (modus == 1) { str1 = a[2]; str2 = a[3]; };
		string line = remove_whitespaces(str);
		line = regex_replace(line, regex("2020"), "  ");
		line = regex_replace(line, regex("20"), " ");
		line = regex_replace(line, regex(str1), "0");
		line = regex_replace(line, regex(str2), "1");
		return morse_decode(trim(line));
	}

private:
	/**
	* A function that converts a string to uppercase letters
	*
	* @param str
	* @return string
	*/
	string stringToUpper(string str)
	{
		transform(str.begin(), str.end(), str.begin(), ::toupper);
		return str;
	}

private:
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
	string strtr(string str, string from, string to)
	{
		vector<string> out;
		for (size_t i = 0, len = str.length(); i < len; i++)
		{
			char c = str.at(i);
			int p = from.find(c);
			if (p >= 0)
			{
				char t = to.at(p);
				out.push_back(string(1, t));
			}
		}
		return !out.empty() ? stringArrToString(out) : str;
	}

private:
	/**
	* Convert a string array into a string <br>
	*
	* @param vstr
	* @return string
	*/
	string stringArrToString(vector<string> vstr)
	{
		string scr = "";
		if (!vstr.empty())
		{
			for (size_t i = 0; i < vstr.size(); i++)
			{
				scr += vstr[i];
			}
		}
		return scr;
	}

private:
	/**
	* trimp automatically strips space at the start and end of a given string <br>
	*
	* @param str
	* @return string
	*/
	string trim(const string& str)
	{
		size_t first = str.find_first_not_of(' ');
		if (string::npos == first)
		{
			return str;
		}
		size_t last = str.find_last_not_of(' ');
		return str.substr(first, (last - first + 1));
	}

private:
	/**
	* Similar to explode in php, a split function on a delimiter <br>
	*
	* @param s
	* @param c
	* @return vector
	*/
	const vector<string> explode(const string& s, const char& c)
	{
		string buff;
		vector<string> vstr;
		for (auto str : s)
		{
			if (str != c)
			{
				buff += str;
			}
			else
			{
				vstr.push_back(buff);
				buff = "";
			}
		}
		if (buff != "")
			vstr.push_back(buff);
		return vstr;
	}

public:
	/**
	* Fix input with whitespace to reduce errors
	* info: regex specialChars{ R"([-[\]{}()*+?.,\^$|#\s])" };
	*
	* @param str
	* @return string
	*/
	string fix_input(string str)
	{
		regex e("[^a-zA-Z0-9!'\"@/_=\\s\\$\\(\\)\\,\\.\\:\\;\\?\\-]+");
		string ret = "";
		sregex_token_iterator iter(str.begin(), str.end(), e, -1), end;
		vector<string> vec(iter, end);
		for (auto a : vec)
		{
			ret += a + " ";
		}
		return trim(ret);
	}

private:
	/**
	* Remove all whitespaces for given string
	*
	* @param str
	* @return string
	*/
	string remove_whitespaces(string str)
	{
		str.erase(remove(str.begin(), str.end(), ' '), str.end());
		return str;
	}
};

int main(int argc, char* argv[])
{
	Morse m;
	double mhz = 880;
	double pitch = 100;
	string action;
	if (argc == 3)
	{
		// arguments part
		if (strcmp(argv[1], "es") == 0) action = "sound";
		if (strcmp(argv[1], "e") == 0) action = "encode";
		if (strcmp(argv[1], "d") == 0) action = "decode";
		if (strcmp(argv[1], "b") == 0) action = "binary";
		if (strcmp(argv[1], "he") == 0) action = "hexa";
		if (strcmp(argv[1], "hd") == 0) action = "hexadec";
		if (strcmp(argv[1], "hb") == 0) action = "hexabin";
		if (strcmp(argv[1], "hbd") == 0) action = "hexabindec";
		if (action == "encode") cout << m.morse_encode(m.fix_input(argv[2])) << "\n";
		if (action == "binary")	cout << m.morse_binary(m.fix_input(argv[2])) << "\n";
		if (action == "decode")	cout << m.morse_decode(m.fix_input(argv[2])) << "\n";
		if (action == "hexa") cout << m.bin_morse_hexadecimal(m.fix_input(argv[2]), 0) << "\n";
		if (action == "hexadec") cout << m.hexadecimal_bin_txt(m.fix_input(argv[2]), 0) << "\n";
		if (action == "hexabin") cout << m.bin_morse_hexadecimal(m.fix_input(argv[2]), 1) << "\n";
		if (action == "hexabindec") cout << m.hexadecimal_bin_txt(m.fix_input(argv[2]), 1) << "\n";
		if (action == "sound")
		{
			string str = m.morse_encode(m.fix_input(argv[2]));
			cout << str << "\n";
			int size = str.size();
			for (size_t i = 0; i < size; ++i)
			{
				char c = str.at(i);
				string s(1, c);
				if (s == ".") Beep(mhz, 1 * pitch);
				if (s == "-") Beep(mhz, 3 * pitch);
				if (s == " ") Beep(0, 3.5 * pitch);
			}
		}
	}
	else
	{
		// console part
		string arg_in;
		cout << "MORSE (cmd line: morse es,e,b,d,he,hd,hb or hbd \"your code or message\")\n";
		cout << "morse table: \nABC DEFGHIJKLMNOPQRSTUVWXYZ 12 34567 890 ! $ ' \" (), . _ - / : ; = ? @ \n";
		cout << "morse actions: \n0 [encode with sound]\n";
		cout << "1 [encode], 2 [binary encode], 3 [decode morse/binary].\n";
		cout << "4 [hexa encode], 5 [hexa decode].\n";
		cout << "6 [hexa bin encode], 7 [hexa bin decode].\n";
		cout << "choose action 0,1,2,3,4,5,6 or 7 and press [enter]:\n";
		getline(cin, arg_in);
		regex e("[0-7]");
		if (!regex_match(arg_in, e))
		{
			arg_in = "1";
			// cursor one column up and erase line. vs studio console and linux only!
			//cout << "\033[A\33[2K" << arg_in << "\n";
			cout << "wrong input, action " << arg_in << " is active now" << "\n";
		}
		if (regex_match(arg_in, e))
		{
			if (arg_in == "0") action = "sound";
			if (arg_in == "1") action = "encode";
			if (arg_in == "2") action = "binary";
			if (arg_in == "3") action = "decode";
			if (arg_in == "4") action = "hexa";
			if (arg_in == "5") action = "hexadec";
			if (arg_in == "6") action = "hexabin";
			if (arg_in == "7") action = "hexabindec";
			cout << "type or paste input and press [enter]\n";
			getline(std::cin, arg_in);
			if (action == "sound")
			{
				string str = m.morse_encode(m.fix_input(arg_in));
				cout << str << "\n";
				int size = str.size();
				for (size_t i = 0; i < size; ++i)
				{
					char c = str.at(i);
					string s(1, c);
					if (s == ".") Beep(mhz, 1 * pitch);
					if (s == "-") Beep(mhz, 3 * pitch);
					if (s == " ") Beep(0, 3.5 * pitch);
				}
			}
			if (action == "encode") cout << m.morse_encode(m.fix_input(arg_in)) << "\n";
			if (action == "binary")	cout << m.morse_binary(m.fix_input(arg_in)) << "\n";
			if (action == "decode")	cout << m.morse_decode(m.fix_input(arg_in)) << "\n";
			if (action == "hexa") cout << m.bin_morse_hexadecimal(m.fix_input(arg_in), 0) << "\n";
			if (action == "hexadec") cout << m.hexadecimal_bin_txt(m.fix_input(arg_in), 0) << "\n";
			if (action == "hexabin") cout << m.bin_morse_hexadecimal(m.fix_input(arg_in), 1) << "\n";
			if (action == "hexabindec") cout << m.hexadecimal_bin_txt(m.fix_input(arg_in), 1) << "\n";
		}
		cout << "Press any key to close program . . .";
		int c = getchar();
		return 0;
	}
}
