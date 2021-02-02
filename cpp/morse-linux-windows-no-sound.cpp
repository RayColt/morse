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
* Derived from ARPANET Pentagon's morse.
*
* Usage program, see: ./morse /help
**/
class Morse
{
/* defaults */
public:
	double frequency_in_hertz = 880.0;// 880 Hz music note A5 - 440 cycles every second
	double words_per_minute = 16.0;//words per minute
	double max_frequency_in_hertz = 8000.0;
	double min_frequency_in_hertz = 37.0;

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
		return morse_map.find(character)->second;
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

public:
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

public:
	/**
	* Calculate words per second to the duration in milliseconds
	*
	* @param wpm - words per minute
	* @return double
	*/
	double duration_milliseconds(double wpm)
	{
		double ms = 0.0;
		if (!wpm <= 0.0)
		{
			//50 elements per word
			double wps = wpm / 60.0; //words per second
			double eps = 50 * wps; //elements per second
			ms = 1000.0 / eps; //milliseconds per element
			return ms;
		}
		else return ms;
	}
	
public:
	/**
	* Reaf cmd line user arguments
	*
	* @param argc
	* @param argv[]
	* @return int
	*/
	int get_options(int argc, char* argv[])
	{
		int args = 0;
		bool ok = false;
		if (strncmp(argv[1], "/help", 5) == 0)
		{
			cout << "morse table : \nABC DEFGHIJKLMNOPQRSTUVWXYZ 12 34567 890 !$ ' \" (), . _ - / : ; = ? @ \n\n";
			cout << "Usage console app version: ./morse\n\n";
			cout << "Usage console line version:\n ./morse e,b,d,he,hd,hb or hbd morse or txt\n\n";
			cout << "e=encode, b=binary-encode, d=decode\n";
			cout << "he=hexadecimal encode, he=hexadecimal decode (2E 2D and 20's)\n";
			cout << "hb=hexadecimal binary encode, hbd=hexadecimal binary decode (30 31 and 20's)\n\n";
			cout << "Example 1: ./morse d \"... ---  ...  ---\"\n";
			cout << "(only with decoding, option d, double quotes are necessary\nto preserve double spaces who create words)\n\n";
			cout << "Example 2: ./morse e hello morse!!\n\n";
			cout << "Have a look at morse.cpp with sound options, only for windows!\n";
			ok = true;
		}
		if (strncmp(argv[1], "e", 1) == 0 || strncmp(argv[1], "b", 1) == 0 || strncmp(argv[1], "d", 1) == 0 ||
			strncmp(argv[1], "he", 2) == 0 || strncmp(argv[1], "hd", 2) == 0 || strncmp(argv[1], "hb", 2) == 0 || strncmp(argv[1], "hbd", 3) == 0)
		{
			ok = true;
		} 
		if(ok == false)
		{
			fprintf(stderr, "option error %s, see ./morse \\help for info\n", argv[2]);
			exit(1);
		}
		return args;
	}

public:
	/**
	* Generate string from arguments
	* @param arg
	* 
	* @return string
	*/
	string arg_string(char* arg)
	{
		char c; string str;
		while ((c = *arg++) != '\0')
		{
			str += c;
		}
		str += " ";
		return str;
	}
};

int main(int argc, char* argv[])
{
	Morse m;
	int n;
	string action = "encode";
	if (argc != 1)
	{
		if (strcmp(argv[1], "es") == 0) action = "sound"; else
		if (strcmp(argv[1], "e") == 0) action = "encode"; else
		if (strcmp(argv[1], "d") == 0) action = "decode"; else
		if (strcmp(argv[1], "b") == 0) action = "binary"; else
		if (strcmp(argv[1], "he") == 0) action = "hexa"; else
		if (strcmp(argv[1], "hd") == 0) action = "hexadec"; else
		if (strcmp(argv[1], "hb") == 0) action = "hexabin"; else
		if (strcmp(argv[1], "hbd") == 0) action = "hexabindec";
		// check options
		n = m.get_options(argc, argv);
		argc -= n;
		argv += n;
		// generate morse code
		string str;
		while (argc > 2) 
		{
			str += m.arg_string(argv[2]);
			argc -= 1;
			argv += 1;
		}
		str = m.trim(m.fix_input(str));
		if (action == "encode") cout << m.morse_encode(str) << "\n"; else
		if (action == "binary") cout << m.morse_binary(str) << "\n"; else
		if (action == "decode") cout << m.morse_decode(str) << "\n"; else
		if (action == "hexa") cout << m.bin_morse_hexadecimal(str, 0) << "\n"; else
		if (action == "hexadec") cout << m.hexadecimal_bin_txt(str, 0) << "\n"; else
		if (action == "hexabin") cout << m.bin_morse_hexadecimal(str, 1) << "\n"; else
		if (action == "hexabindec") cout << m.hexadecimal_bin_txt(str, 1) << "\n";
	}
	else
	{
		// console part
		string arg_in;
		cout << "MORSE (cmd line: [./morse /help] for info)\n";
		cout << "morse table: \nABC DEFGHIJKLMNOPQRSTUVWXYZ 12 34567 890 ! $ ' \" (), . _ - / : ; = ? @ \n";
		cout << "morse actions:\n";
		cout << "1 [encode], 2 [binary encode], 3 [decode morse/binary].\n";
		cout << "4 [hexa encode], 5 [hexa decode].\n";
		cout << "6 [hexa bin encode], 7 [hexa bin decode].\n";
		cout << "choose action 1,2,3,4,5,6 or 7 and press [enter]:\n";
		getline(cin, arg_in);
		regex e("[0-7]");
		if (!regex_match(arg_in, e))
		{
			arg_in = "1";
			cout << "wrong input, action " << arg_in << " is active now" << "\n";
		}
		if (regex_match(arg_in, e))
		{
			if (arg_in == "1") action = "encode"; else
			if (arg_in == "2") action = "binary"; else
			if (arg_in == "3") action = "decode"; else
			if (arg_in == "4") action = "hexa"; else
			if (arg_in == "5") action = "hexadec"; else
			if (arg_in == "6") action = "hexabin"; else
			if (arg_in == "7") action = "hexabindec";
			cout << "type or paste input and press [enter]\n";
			getline(std::cin, arg_in);
			arg_in = m.fix_input(arg_in);
			if (action == "encode") cout << m.morse_encode(arg_in) << "\n"; else
			if (action == "binary") cout << m.morse_binary(arg_in) << "\n"; else
			if (action == "decode") cout << m.morse_decode(arg_in) << "\n"; else
			if (action == "hexa") cout << m.bin_morse_hexadecimal(arg_in, 0) << "\n"; else
			if (action == "hexadec") cout << m.hexadecimal_bin_txt(arg_in, 0) << "\n"; else
			if (action == "hexabin") cout << m.bin_morse_hexadecimal(arg_in, 1) << "\n"; else
			if (action == "hexabindec") cout << m.hexadecimal_bin_txt(arg_in, 1) << "\n";
		}
		cout << "Press any key to close program . . .";
		int c = getchar();
		return 0;
	}
}
