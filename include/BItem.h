/**
* @file      BItem.h
* @copyright (c) 2014 by Petr Zemek (s3rvac@gmail.com) and contributors
* @license   BSD, see the @c LICENSE file for more details
* @brief     Base class for all items (integers, strings, etc.).
*/

#ifndef BENCODING_BITEM_H
#define BENCODING_BITEM_H

namespace bencoding {

/**
* @brief Base class for all items (integers, strings, etc.).
*/
class BItem {
public:
	virtual ~BItem() = 0;
};

} // namespace bencoding

#endif
