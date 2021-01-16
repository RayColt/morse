#include <string>
#include <iostream>
#include <map>
#include <iterator>
#include <vector>
#include <regex>

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
* .\morse.exe e "morse is fun!!" OR .\morse.exe "e" "morse is fun!!"
**/
class Morse
{
public:
	Morse() { fill_morse_maps(); }

	multimap <string, string> morse_map;
	multimap <string, string> morse_map_reversed;
	void fill_morse_maps()
	{
		morse_map.insert(std::pair <std::string, std::string>(" ", ""));        // SPACE (0b1)
		morse_map.insert(std::pair <std::string, std::string>("!", "101011"));  // -.-.--
		morse_map.insert(std::pair <std::string, std::string>("$", "0001001")); // ...-..-
		morse_map.insert(std::pair <std::string, std::string>("\"", "010010")); // .-..-.

		morse_map.insert(std::pair <std::string, std::string>("'", "011110"));  // .----.
		morse_map.insert(std::pair <std::string, std::string>("(", "10110"));   // -.--.
		morse_map.insert(std::pair <std::string, std::string>(")", "101101"));  // -.--.-

		morse_map.insert(std::pair <std::string, std::string>(",", "110011"));  // --..--
		morse_map.insert(std::pair <std::string, std::string>("-", "100001"));  // -....-
		morse_map.insert(std::pair <std::string, std::string>(".", "010101"));  // .-.-.-
		morse_map.insert(std::pair <std::string, std::string>("/", "10010"));   // -..-.

		morse_map.insert(std::pair <std::string, std::string>("0", "11111"));   // -----
		morse_map.insert(std::pair <std::string, std::string>("1", "01111"));   // .----
		morse_map.insert(std::pair <std::string, std::string>("2", "00111"));   // ..---
		morse_map.insert(std::pair <std::string, std::string>("3", "00011"));   // ...--
		morse_map.insert(std::pair <std::string, std::string>("4", "00001"));   // ....-
		morse_map.insert(std::pair <std::string, std::string>("5", "00000"));   // .....
		morse_map.insert(std::pair <std::string, std::string>("6", "10000"));   // -....
		morse_map.insert(std::pair <std::string, std::string>("7", "11000"));   // --...
		morse_map.insert(std::pair <std::string, std::string>("8", "11100"));   // ---..
		morse_map.insert(std::pair <std::string, std::string>("9", "11110"));   // ----.

		morse_map.insert(std::pair <std::string, std::string>(":", "111000"));  // ---...
		morse_map.insert(std::pair <std::string, std::string>(";", "101010"));  // -.-.-.
		morse_map.insert(std::pair <std::string, std::string>("=", "10001"));   // -...-
		morse_map.insert(std::pair <std::string, std::string>("?", "001100"));  // ..--..
		morse_map.insert(std::pair <std::string, std::string>("@", "011010"));  // .--.-.

		morse_map.insert(std::pair <std::string, std::string>("A", "01"));      // .-
		morse_map.insert(std::pair <std::string, std::string>("B", "1000"));    // -...
		morse_map.insert(std::pair <std::string, std::string>("C", "1010"));    // -.-.
		morse_map.insert(std::pair <std::string, std::string>("D", "100"));     // -..
		morse_map.insert(std::pair <std::string, std::string>("E", "0"));       // .
		morse_map.insert(std::pair <std::string, std::string>("F", "0010"));    // ..-.
		morse_map.insert(std::pair <std::string, std::string>("G", "110"));     // --.
		morse_map.insert(std::pair <std::string, std::string>("H", "0000"));    // ....
		morse_map.insert(std::pair <std::string, std::string>("I", "00"));      // ..
		morse_map.insert(std::pair <std::string, std::string>("J", "0111"));    // .---
		morse_map.insert(std::pair <std::string, std::string>("K", "101"));     // -.-
		morse_map.insert(std::pair <std::string, std::string>("L", "0100"));    // .-..
		morse_map.insert(std::pair <std::string, std::string>("M", "11"));      // --
		morse_map.insert(std::pair <std::string, std::string>("N", "10"));      // -.
		morse_map.insert(std::pair <std::string, std::string>("O", "111"));     // ---
		morse_map.insert(std::pair <std::string, std::string>("P", "0110"));    // .--.
		morse_map.insert(std::pair <std::string, std::string>("Q", "1101"));    // --.-
		morse_map.insert(std::pair <std::string, std::string>("R", "010"));     // .-.
		morse_map.insert(std::pair <std::string, std::string>("S", "000"));     // ...
		morse_map.insert(std::pair <std::string, std::string>("T", "1"));       // -
		morse_map.insert(std::pair <std::string, std::string>("U", "001"));     // ..-
		morse_map.insert(std::pair <std::string, std::string>("V", "0001"));    // ...-
		morse_map.insert(std::pair <std::string, std::string>("W", "011"));     // .--
		morse_map.insert(std::pair <std::string, std::string>("X", "1001"));    // -..-
		morse_map.insert(std::pair <std::string, std::string>("Y", "1011"));    // -.--
		morse_map.insert(std::pair <std::string, std::string>("Z", "1100"));    // --..
		morse_map.insert(std::pair <std::string, std::string>("_", "001101"));  // ..--.-
		morse_map.insert(std::pair <std::string, std::string>("ERR", "00000000")); // ........
		// invert morse_map
		for (const auto& it : morse_map)
		{
			morse_map_reversed.insert(make_pair(it.second, it.first));
		}
	}

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

	/**
	* Get character string for given morse code
	*
	* @param str
	* @return string
	*/
	string morse_decode(string str)
	{
		string line = "";
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
		for (auto a : vec) {
			ret += a + " ";
		}
		return ret;
	}
};

int main(int argc, char* argv[])
{
	Morse m;
	string action;
	if (argc == 3)
	{
		// arguments part
		if (strcmp(argv[1], "e") == 0) action = "encode";
		if (strcmp(argv[1], "d") == 0) 	action = "decode";
		if (strcmp(argv[1], "b") == 0) 	action = "binary";
		if (action == "encode") cout << m.morse_encode(m.fix_input(argv[2])) << "\n";
		if (action == "binary")	cout << m.morse_binary(m.fix_input(argv[2])) << "\n";
		if (action == "decode")	cout << m.morse_decode(m.fix_input(argv[2])) << "\n";
	}
	else
	{
		// console part
		string arg_in;
		cout << "morse table: \nABC DEFGHIJKLMNOPQRSTUVWXYZ 12 34567 890 ! $ ' \" (), . _ - / : ; = ? @ \n";
		cout << "morse actions: 1 [encode], 2 [binary morse encode], 3 [decode].\n";
		cout << "choose action 1, 2 or 3 and press [enter]\n";
		getline(cin, arg_in); regex e("[1-3]");
		if (!regex_match(arg_in, e))
		{
			arg_in = "1";
			// cursor one column up and erase line. vs studio and linux only!
			//cout << "\033[A\33[2K" << arg_in << "\n";
			cout << "wrong input, action " << arg_in << " is active now" << "\n";
		}
		if (arg_in == "1") action = "encode";
		if (arg_in == "2") action = "binary";
		if (arg_in == "3") action = "decode";
		cout << "type or paste input and press [enter]\n";
		getline(std::cin, arg_in);
		if (action == "encode") cout << m.morse_encode(m.fix_input(arg_in)) << "\n";
		if (action == "binary")	cout << m.morse_binary(m.fix_input(arg_in)) << "\n";
		if (action == "decode")	cout << m.morse_decode(m.fix_input(arg_in)) << "\n";
		cout << "Press any key to close program . . .";
		int c = getchar();
		return 0;
	}
}
