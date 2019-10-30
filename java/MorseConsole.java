package morsepack;
import java.io.BufferedReader;
import java.io.IOException;
import java.io.InputStreamReader;

public class MorseConsole {

	public static void main(String[] args) {
		new MorseConsole();
		Morse morse = new Morse();
		BufferedReader reader = new BufferedReader(new InputStreamReader(System.in));
		System.out.println("..-- Power Morse Coder --..");
		String encode = "";
		String decode = "";
		try {
			System.out.println("encode:");
			encode = reader.readLine();
			if (!morse.isEmpty(encode)) {
				System.out.println(morse.morse_encode(encode));
				System.out.println(morse.morse_binary(encode));
			}
			System.out.println("decode:");
			decode = reader.readLine();
			if (!morse.isEmpty(decode))
				System.out.println(morse.morse_decode(decode));
			reader.readLine();
		} catch (IOException e) {
			System.out.println("ERROR: " + e.getStackTrace());
		}
	}
}
