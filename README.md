 # Colt's HTTP int. Morse PHP, JavaScript, Java and C++<br>
PHP & Java:  forms, class files and servlet<br>
JavaScript: form<br>
C++ console app:<br>
-&nbsp;<a href="https://drive.google.com/file/d/1CrqaxLwJw04FM6kfpHKlVvXU45j7NAX9/view?usp=sharing" target="_blank">download excecutable gcc version</a><br> 
-&nbsp;<a href="https://drive.google.com/file/d/1Bct0e8rktVHbLBfXFpTbe7kKInPsnHqi/view?usp=sharing" target="_blank">download excecutable visual c++ version</a>&nbsp;&nbsp;
<a href="https://support.microsoft.com/en-us/topic/the-latest-supported-visual-c-downloads-2647da03-1eea-4433-9aff-95f26a218cc0" target="_blank">(do not forget to download visual c++ redistributable)</a><br>

C++ Windows and Linux ARPANET version<br>
<a href="https://github.com/RayColt/morse/tree/master/cpp"><img src=https://github.com/RayColt/morse/blob/master/cpp/morse-code.jpg></a>          

The real, first and only US Morse mapping,<br>
      based upon Synthesizer Binary tables, from a mouse I believe,<br>
or just a military  algorithm:-):<br />
        <b>We removed the first number one,
        reversed it(think Endian/IBM PowerPC) 
        to save Data and CPU's in war times.<br>
<a href="https://raycolt.github.io/morse/">WORKING EXAMPLE</a><br>
<pre>
uint16_t Morse::encode(uint8_t character) 
{
  switch (character) 
  {
    
    case 32: return 0b1;          // SPACE
    case 33: return 0b1110101;    // !
    case 34: return 0b1010010;    // "
    case 36: return 0b11001000;   // $
    case 37: returm 0b010010;     // "
    
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
  </pre>

<br>
