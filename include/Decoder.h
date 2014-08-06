/**
* @file      Decoder.h
* @copyright (c) 2014 by Petr Zemek (s3rvac@gmail.com) and contributors
* @license   BSD, see the @c LICENSE file for more details
* @brief     Decoder of bencoded data.
*/

#ifndef BENCODING_DECODER_H
#define BENCODING_DECODER_H

#include <exception>
#include <memory>
#include <string>

#include "BItem.h"

namespace bencoding {

class BInteger;

/**
* @brief Exception thrown when there is an error during the decoding.
*/
class DecodingError: public std::runtime_error {
public:
	explicit DecodingError(const std::string &what);
};

/**
* @brief Decoder of bencoded data.
*
* The format is based on the <a
* href="https://wiki.theory.org/BitTorrentSpecification#Bencoding">BitTorrent
* specification</a>.
*
* Use create() to create instances.
*/
class Decoder {
public:
	static std::unique_ptr<Decoder> create();

	std::unique_ptr<BItem> decode(const std::string &data) const;
	std::unique_ptr<BItem> decode(std::istream &input) const;

private:
	Decoder();

	std::unique_ptr<BInteger> decodeInteger(std::istream &input) const;
	std::string readEncodedInteger(std::istream &input) const;
	std::unique_ptr<BInteger> decodeEncodedInteger(
		const std::string &encodedInteger) const;
};

} // namespace bencoding

#endif
