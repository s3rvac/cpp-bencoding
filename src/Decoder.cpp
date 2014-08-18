/**
* @file      Decoder.cpp
* @copyright (c) 2014 by Petr Zemek (s3rvac@gmail.com) and contributors
* @license   BSD, see the @c LICENSE file for more details
* @brief     Implementation of the Decoder class.
*/

#include "Decoder.h"

#include <cassert>
#include <regex>
#include <sstream>

#include "BInteger.h"
#include "BString.h"
#include "Utils.h"

namespace bencoding {

/**
* @brief Constructs a new exception with the given message.
*/
DecodingError::DecodingError(const std::string &what):
	std::runtime_error(what) {}

/**
* @brief Constructs a decoder.
*/
Decoder::Decoder() {}

/**
* @brief Creates a new decoder.
*/
std::unique_ptr<Decoder> Decoder::create() {
	return std::unique_ptr<Decoder>(new Decoder());
}

/**
* @brief Decodes the given bencoded @a data and returns them.
*/
std::unique_ptr<BItem> Decoder::decode(const std::string &data) {
	std::istringstream input(data);
	return decode(input);
}

/**
* @brief Reads all the data from the given @a input, decodes them and returns
*        them.
*/
std::unique_ptr<BItem> Decoder::decode(std::istream &input) {
	switch (input.peek()) {
		case 'i':
			return decodeInteger(input);
		case '0':
		case '1':
		case '2':
		case '3':
		case '4':
		case '5':
		case '6':
		case '7':
		case '8':
		case '9':
			return decodeString(input);
		default:
			throw DecodingError(std::string("unexpected character: '") +
				static_cast<char>(input.peek()) + "'");
	}

	assert(false && "should never happen");
	return std::unique_ptr<BItem>();
}

/**
* @brief Decodes an integer from @a input.
*
* @par Format
* @code
* i<integer encoded in base ten ASCII>e
* @endcode
*
* @par Example
* @code
* i3e represents the integer 3
* @endcode
*
* Moreover, only the significant digits should be used, one cannot pad the
* integer with zeroes, such as @c i04e (see the <a
* href="https://wiki.theory.org/BitTorrentSpecification#Bencoding">
* specification</a>).
*/
std::unique_ptr<BInteger> Decoder::decodeInteger(std::istream &input) const {
	return decodeEncodedInteger(readEncodedInteger(input));
}

/**
* @brief Reads an encoded integer from @a input.
*/
std::string Decoder::readEncodedInteger(std::istream &input) const {
	// See the description of decodeInteger() for the format and example.
	std::string encodedInteger;
	bool encodedIntegerReadCorrectly = readUntil(input, encodedInteger, 'e');
	if (!encodedIntegerReadCorrectly) {
		throw DecodingError("error during the decoding of an integer near '" +
			encodedInteger + "'");
	}

	return encodedInteger;
}

/**
* @brief Decodes the given encoded integer.
*/
std::unique_ptr<BInteger> Decoder::decodeEncodedInteger(
		const std::string &encodedInteger) const {
	// See the description of decodeInteger() for the format and example.
	std::regex integerRegex("i([-+]?(0|[1-9][0-9]*))e");
	std::smatch match;
	bool valid = std::regex_match(encodedInteger, match, integerRegex);
	if (!valid) {
		throw DecodingError("encountered an encoded integer of invalid format: '" +
			encodedInteger + "'");
	}

	BInteger::ValueType integerValue;
	strToNum(match[1].str(), integerValue);
	return BInteger::create(integerValue);
}

/**
* @brief Decodes a string from @a input.
*
* @par Format
* @code
* <string length encoded in base ten ASCII>:<string data>
* @endcode
*
* @par Example
* @code
* 4:test represents the string "test"
* @endcode
*/
std::unique_ptr<BString> Decoder::decodeString(std::istream &input) const {
	std::string::size_type stringLength(readStringLength(input));
	readColon(input);
	std::string str(readStringOfGivenLength(input, stringLength));
	return BString::create(str);
}

/**
* @brief Reads the string length from @a input, validates it, and returns it.
*/
std::string::size_type Decoder::readStringLength(std::istream &input) const {
	std::string stringLengthInASCII;
	bool stringLengthInASCIIReadCorrectly = readUpTo(input, stringLengthInASCII, ':');
	if (!stringLengthInASCIIReadCorrectly) {
		throw DecodingError("error during the decoding of a string near '" +
			stringLengthInASCII + "'");
	}

	std::string::size_type stringLength;
	bool stringLengthIsValid = strToNum(stringLengthInASCII, stringLength);
	if (!stringLengthIsValid) {
		throw DecodingError("invalid string length: '" + stringLengthInASCII + "'");
	}

	return stringLength;
}

/**
* @brief Reads a colon from @a input and discards it.
*/
void Decoder::readColon(std::istream &input) const {
	int c = input.get();
	if (c != ':') {
		throw DecodingError("expected a colon (':'), got '" +
			std::to_string(static_cast<char>(c)) + "'");
	}
}

/**
* @brief Reads a string of the given @a length from @a input and returns it.
*/
std::string Decoder::readStringOfGivenLength(std::istream &input,
		std::string::size_type length) const {
	std::string str(length, char());
	input.read(&str[0], length);
	std::string::size_type numOfReadChars(input.gcount());
	if (numOfReadChars != length) {
		throw DecodingError("expected a string containing " + std::to_string(length) +
			" characters, but read only " + std::to_string(numOfReadChars) +
			" characters");
	}
	return str;
}

} // namespace bencoding
