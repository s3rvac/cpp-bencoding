/**
* @file      PrettyPrinter.h
* @copyright (c) 2014 by Petr Zemek (s3rvac@gmail.com) and contributors
* @license   BSD, see the @c LICENSE file for more details
* @brief     Pretty printer of data.
*/

#ifndef BENCODING_PRETTYPRINTER_H
#define BENCODING_PRETTYPRINTER_H

#include <memory>
#include <string>

#include "BItemVisitor.h"

namespace bencoding {

class BItem;

/**
* @brief Pretty printer of data.
*
* Can format data in a readable way.
*
* Use create() to create instances.
*/
class PrettyPrinter: private BItemVisitor {
public:
	static std::unique_ptr<PrettyPrinter> create();

	std::string getPrettyRepr(std::shared_ptr<BItem> data);

private:
	PrettyPrinter();

	/// @name BItemVisitor Interface
	/// @{
	virtual void visit(BInteger *bInteger) override;
	virtual void visit(BString *bString) override;
	/// @}

private:
	/// Pretty representation of data obtained so far.
	std::string prettyRepr;
};

} // namespace bencoding

#endif