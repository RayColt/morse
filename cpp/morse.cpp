#include <string> 
#include <iostream>
#include <map> 
#include <iterator>
#include <algorithm>
#include <vector>
#include <regex>
#include <sstream>
#include <functional>
/**
* C++ Morse
*
* @author Ray Colt <ray_colt@pentagon.mil>
* @copyright Copyright (c) 1975 Ray Colt
* @license Public General License US Army
*
**/
using namespace std;

multimap <string, string> morse_map;
multimap <string, string> morse_map_reversed;
void fill_morse_maps();
string getBinChar(string character);
string getMorse(string character);
string getCharacter(string morse);
string stringToUpper(string strToConvert);
string strtr(string str, string from, string to);
string trim(const string& str);
const vector<string> explode(const string& s, const char& c);
string stringArrToString(vector<string> vstr);
string morse_binary(string str);
string morse_encode(string str);
string morse_decode(string str);

int main()
{
	fill_morse_maps();
	// command line part
	string arg_in;
	cout << "morse actions: 1 [encode], 2 [binary morse encode], 3 [decode].\n";
	cout << "choose action 1, 2 or 3\n";
	getline(std::cin, arg_in); string action;
	if (arg_in == "1")
		action = "encode";
	if (arg_in == "2")
		action = "binary";
	if (arg_in == "3")
		action = "decode";
	cout << "type or paste input and press <enter>\n";
	getline(std::cin, arg_in);
	if (action == "encode")
		cout << morse_encode(arg_in) << "\n";
	if (action == "binary")
		cout << morse_binary(arg_in) << "\n";
	if (action == "decode")
		cout << morse_decode(arg_in) << "\n";
	system("pause");
	cout << "Press any key to continue . . .";
	return 0;
}

void fill_morse_maps()
{
	morse_map.insert(pair <string, string>(" ", "")); // SPACE (0b1)
	morse_map.insert(pair <string, string>("!", "101011")); // -.-.--
	morse_map.insert(pair <string, string>("\"", "010010")); // .-..-.
	morse_map.insert(pair <string, string>("$", "0001001")); // ...-..-

	morse_map.insert(pair <string, string>("'", "011110")); // .----.
	morse_map.insert(pair <string, string>("(", "10110")); // -.--.
	morse_map.insert(pair <string, string>(")", "101101")); // -.--.-

	morse_map.insert(pair <string, string>(",", "110011")); // --..--
	morse_map.insert(pair <string, string>("-", "100001")); // -....-
	morse_map.insert(pair <string, string>(".", "010101")); // .-.-.-
	morse_map.insert(pair <string, string>("/", "10010")); // -..-.

	morse_map.insert(pair <string, string>("0", "11111")); // -----
	morse_map.insert(pair <string, string>("1", "01111")); // .----
	morse_map.insert(pair <string, string>("2", "00111")); // ..---
	morse_map.insert(pair <string, string>("3", "00011")); // ...--
	morse_map.insert(pair <string, string>("4", "00001")); // ....-
	morse_map.insert(pair <string, string>("5", "00000")); // .....
	morse_map.insert(pair <string, string>("6", "10000")); // -....
	morse_map.insert(pair <string, string>("7", "11000")); // --...
	morse_map.insert(pair <string, string>("8", "11100")); // ---..
	morse_map.insert(pair <string, string>("9", "11110")); // ----.

	morse_map.insert(pair <string, string>(":", "111000")); // ---...
	morse_map.insert(pair <string, string>(";", "101010")); // -.-.-.
	morse_map.insert(pair <string, string>("=", "10001")); // -...-
	morse_map.insert(pair <string, string>("?", "001100")); // ..--..
	morse_map.insert(pair <string, string>("@", "011010")); // .--.-.

	morse_map.insert(pair <string, string>("A", "01")); // .-
	morse_map.insert(pair <string, string>("B", "1000")); // -...
	morse_map.insert(pair <string, string>("C", "1010")); // -.-.
	morse_map.insert(pair <string, string>("D", "100")); // -..
	morse_map.insert(pair <string, string>("E", "0")); // .
	morse_map.insert(pair <string, string>("F", "0010")); // ..-.
	morse_map.insert(pair <string, string>("G", "110")); // --.
	morse_map.insert(pair <string, string>("H", "0000")); // ....
	morse_map.insert(pair <string, string>("I", "00")); // ..
	morse_map.insert(pair <string, string>("J", "0111")); // .---
	morse_map.insert(pair <string, string>("K", "101")); // -.-
	morse_map.insert(pair <string, string>("L", "0100")); // .-..
	morse_map.insert(pair <string, string>("M", "11")); // --
	morse_map.insert(pair <string, string>("N", "10")); // -.
	morse_map.insert(pair <string, string>("O", "111")); // ---
	morse_map.insert(pair <string, string>("P", "0110")); // .--.
	morse_map.insert(pair <string, string>("Q", "1101")); // --.-
	morse_map.insert(pair <string, string>("R", "010")); // .-.
	morse_map.insert(pair <string, string>("S", "000")); // ...
	morse_map.insert(pair <string, string>("T", "1")); // -
	morse_map.insert(pair <string, string>("U", "001")); // ..-
	morse_map.insert(pair <string, string>("V", "0001")); // ...-
	morse_map.insert(pair <string, string>("W", "011")); // .--
	morse_map.insert(pair <string, string>("X", "1001")); // -..-
	morse_map.insert(pair <string, string>("Y", "1011")); // -.--
	morse_map.insert(pair <string, string>("Z", "1100")); // --..
	morse_map.insert(pair <string, string>("_", "001101")); // ..--.-
	morse_map.insert(pair <string, string>("ERR", "00000000")); // ........
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
string morse_binary(string str) {
	string line = "";
	for (int i = 0; i < str.length(); i++) {
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
string morse_encode(string str) {
	string line = "";
	for (int i = 0; i < str.length(); i++) {
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
string morse_decode(string str) {
	string line = "";
	vector<string> morsecodes = explode(str, ' ');
	for (auto morse : morsecodes)
	{
		if (morse.empty())
			line += " ";
		string chr = getCharacter(morse);
		line += chr;
	}
	regex e ("\\s{2,}");
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
	for (int i = 0, len = str.length(); i < len; i++)
	{
		char c = str.at(i);
		int p = from.find(c);

		if (p >= 0)
		{
			char t = to.at(p);
			out.push_back(std::string(1, t));
		}
	}
	if (!out.empty())
		return stringArrToString(out);
	else
		return str;
}

/**
* Convert a string array into a string <br>
*
* @param vstr
* @return string
*/
string stringArrToString(vector<string> vstr)
{
	string scr ="";
	if (!vstr.empty())
	{
		for (int i = 0; i<vstr.size(); i++) 
		{
			scr += vstr[i];// copy the vector to the string
		}
	}
	return scr;
}

/**
* trimp automatically strips space at the start and end of a given string <br>
*
* @param sstr
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
	for (auto n : s)
	{
		if (n != c) 
			buff += n; 
		else
			if (n == c)// && buff != "") 
			{ 
				vstr.push_back(buff);
				buff = ""; 
			}
	}
	if (buff != "") 
		vstr.push_back(buff);
	return vstr;
}
