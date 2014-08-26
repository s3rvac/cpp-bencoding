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

	std::string getPrettyRepr(std::shared_ptr<BItem> data,
		const std::string &indent = "    ");
	std::string getPrettyReprWithoutIndent(std::shared_ptr<BItem> data);

private:
	PrettyPrinter();

	/// @name BItemVisitor Interface
	/// @{
	virtual void visit(BDictionary *bDictionary) override;
	virtual void visit(BInteger *bInteger) override;
	virtual void visit(BList *bList) override;
	virtual void visit(BString *bString) override;
	/// @}

	/// @name Indentation
	/// @{
	void storeCurrentIndent();
	void increaseIndentLevel();
	void decreaseIndentLevel();
	/// @}

	/// @name Formatting
	/// @{
	void formatAndStoreWithIndent(BDictionary *bDictionary);
	void formatAndStoreWithoutIndent(BDictionary *bDictionary);
	void formatAndStore(BInteger *bInteger);
	void formatAndStoreWithIndent(BList *bList);
	void formatAndStoreWithoutIndent(BList *bList);
	void formatAndStore(BString *bString);
	/// @}

private:
	/// Pretty representation of the data obtained so far.
	std::string prettyRepr = "";

	/// A single level of indentation.
	std::string indentLevel = "    ";

	/// The current level of indentation.
	std::string currentIndent = "";

	/// Should we perform indentation?
	bool indent = true;
};

/// @name Printing Without Explicit Printer Creation
/// @{
std::string getPrettyRepr(std::shared_ptr<BItem> data,
	const std::string &indent = "    ");
std::string getPrettyReprWithoutIndent(std::shared_ptr<BItem> data);
/// @}

} // namespace bencoding

#endif
