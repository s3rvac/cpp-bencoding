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
* @brief Decodes the given bencoded data and returns them.
*/
std::unique_ptr<BItem> Decoder::decode(const std::string &data) const {
	std::istringstream input{data};
	return decode(input);
}

/**
* @brief Reads all the data from the given @a input, decodes them and returns
*        them.
*/
std::unique_ptr<BItem> Decoder::decode(std::istream &input) const {
	switch (input.peek()) {
		case 'i':
			return decodeInteger(input);
		default:
			throw DecodingError("unexpected character: '" +
				std::to_string(input.peek()) + "'");
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
	std::regex integerRegex{"i([-+]?[0-9]+)e"};
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

} // namespace bencoding
