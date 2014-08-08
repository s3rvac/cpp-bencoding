/**
* @file      Encoder.cpp
* @copyright (c) 2014 by Petr Zemek (s3rvac@gmail.com) and contributors
* @license   BSD, see the @c LICENSE file for more details
* @brief     Implementation of the Encoder class.
*/

#include "Encoder.h"

#include "BInteger.h"
#include "BString.h"
#include "Utils.h"

namespace bencoding {

/**
* @brief Constructs an encoder.
*/
Encoder::Encoder() {}

/**
* @brief Creates a new encoder.
*/
std::unique_ptr<Encoder> Encoder::create() {
	return std::unique_ptr<Encoder>(new Encoder());
}

/**
* @brief Encodes the given @a data and returns them.
*/
std::string Encoder::encode(std::shared_ptr<BItem> data) {
	clear(encodedItems);
	data->accept(this);
	return encodedItems.top();
}

void Encoder::visit(BInteger *bInteger) {
	// See the description of Decoder::decodeInteger() for the format and
	// example.
	std::string encodedInteger("i" + std::to_string(bInteger->value()) + "e");
	encodedItems.push(encodedInteger);
}

void Encoder::visit(BString *bString) {
	// See the description of Decoder::decodeString() for the format and
	// example.
	std::string encodedString(
		std::to_string(bString->length()) + ":" + bString->value()
	);
	encodedItems.push(encodedString);
}

} // namespace bencoding
