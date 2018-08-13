/*  Base64 Algorithm 

	Base64 Chart:

	 ------------------------------------------------------
	|  A  |  B  |  C  |  D  | ... |  8  |  9  |  +  |  /  |
	 ------------------------------------------------------
	|  0  |  1  |  2  |  3  | ... | 60  | 61  | 62  | 63  |
	 ------------------------------------------------------

	 Chart includes (64 characters): 
	 ABCDEFGHIJKLMNOPQRSTUVWXYZabcdefghijklmnopqrstuvwxyz0123456789+/

	 For an example of how this encoding process works we will use the 
	 word "Code" which is "Q29kZQ==" in its Base64 encoded form.

	 1) When you take the letters of "Code" and translate each one into
	 ASCII values we get:
		C = 067
		o = 111
		d = 100
		e = 101

	2) Translated into 8-bit binary these ASCII values are:
		067 = 01000011
		111 = 01101111
		100 = 01100100
		101 = 01100101

	3) The binary values grouped together (8x4 = 32 bits):
		01000011 + 01101111 + 01100100 + 01100101 =
		01000011011011110110010001100101

	4) Then this 32-bit number is grouped into groups of 6 
	(because 2^6 = 64 and this allows us to group them into our chart)

		 -----------------------------------------
		|010000|110110|111101|100100|011001|010000|  <-- add 4 zeros to last group
		 -----------------------------------------
		|			Convert to Decimal			  |	
		 -----------------------------------------
		|  16  |  54  |  61  |  36  |  25  |  16  |
		 -----------------------------------------
		|	  Convert Decimal to Base64 values	  |
		 -----------------------------------------
		|  Q   |  2   |  9   |  k   |  Z   |  Q   |
		 -----------------------------------------

	5) This gives us "Q29kZQ", but because we had a group of less than
	   6 bits, we have to add "padding" to this value, which is a "="
	   symbol. If our number (32) % 3 is equal to 1 byte, we add two
	   equal signs to our value as padding, resulting in in the final 
	   encoded value of: "Q29kZQ=="

	   If the bit number divided by 3 resulted in a remainder of 2 bytes
	   then we would only add one equal sign for padding. Here are the 
	   respective formulas:
	   
	   n % 3 = 1(byte) --> then we add "==" at the end for padding
	   n % 3 = 2(byte) --> then we add "=" at the end for padding
	   




 */
#ifndef BASE64_H
#define BASE64_H

#include <vector>
#include <string>

namespace Base64
{
	std::string base64_encode(const std::string &);

	const std::string &saltHash1 = "30//99:/WW";
	const std::string &saltHash2 = "!falcon!!kong";
	const std::string &saltHash3 = "_SOUL=*DARK>>";

	std::string encrypt64(std::string inputStr)
	{
		inputStr = saltHash1 + inputStr + saltHash2 + saltHash3;
		inputStr = base64_encode(inputStr);
		inputStr.insert(7, saltHash3);
		inputStr += saltHash1;
		inputStr = base64_encode(inputStr);
		inputStr = saltHash2 + saltHash3 + saltHash1;
		inputStr = base64_encode(inputStr);
		inputStr.insert(1, "L");
		inputStr.insert(7, "M");

		return inputStr;
	}

	const std::string &BASE64_CODES = 
		"ABCDEFGHIJKLMNOPQRSTUVWXYZabcdefghijklmnopqrstuvwxyz0123456789+/";

	std::string base64_encode(const std::string &str)
	{
		std::string outStr;
		int value = 0;
		int bits = -6;
		const unsigned int b63 = 0x3F;

		for (const auto &charSign : str)
		{
			value = (value << 8) + charSign;
			bits += 8;

			while (bits >= 0)
			{
				outStr.push_back(BASE64_CODES[(value >> bits) & b63]);
				bits -= 6;
			}
		}

		if (bits > -6)
		{
			outStr.push_back(BASE64_CODES[((value << 8) >> (bits + 8)) & b63]);
		}
			

		while (outStr.size() % 4)
		{
			outStr.push_back('=');
		}

		return outStr;
	}

}

#endif // BASE64_H
