/**
* @file      Decoder.h
* @copyright (c) 2014 by Petr Zemek (s3rvac@gmail.com) and contributors
* @license   BSD, see the @c LICENSE file for more details
* @brief     Decoder of bencoded data.
*/

#ifndef BENCODING_DECODER_H
#define BENCODING_DECODER_H

#include <memory>
#include <string>

#include "BItem.h"

namespace bencoding {

/**
* @brief Decoder of bencoded data.
*
* Use create() to create instances.
*/
class Decoder {
public:
	static std::unique_ptr<Decoder> create();

	std::unique_ptr<BItem> decode(const std::string &data) const;
	std::unique_ptr<BItem> decode(std::istream &input) const;

public:
	Decoder();
};

} // namespace bencoding

#endif
