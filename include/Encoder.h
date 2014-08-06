/**
* @file      Encoder.h
* @copyright (c) 2014 by Petr Zemek (s3rvac@gmail.com) and contributors
* @license   BSD, see the @c LICENSE file for more details
* @brief     Encoder of bencoded data.
*/

#ifndef BENCODING_ENCODER_H
#define BENCODING_ENCODER_H

#include <memory>
#include <stack>
#include <string>

#include "BItemVisitor.h"

namespace bencoding {

class BItem;

/**
* @brief Encoder of bencoded data.
*
* The format is based on the <a
* href="https://wiki.theory.org/BitTorrentSpecification#Bencoding">BitTorrent
* specification</a>.
*
* Use create() to create instances.
*/
class Encoder: private BItemVisitor {
public:
	static std::unique_ptr<Encoder> create();

	std::string encode(std::shared_ptr<BItem> data);

private:
	Encoder();

	/// @name BItemVisitor Interface
	/// @{
	virtual void visit(BInteger *bInteger) override;
	/// @}

private:
	/// Stack of encoded items.
	std::stack<std::string> encodedItems;
};

} // namespace bencoding

#endif
