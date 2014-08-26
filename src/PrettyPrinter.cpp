/**
* @file      PrettyPrinter.cpp
* @copyright (c) 2014 by Petr Zemek (s3rvac@gmail.com) and contributors
* @license   BSD, see the @c LICENSE file for more details
* @brief     Implementation of the PrettyPrinter class.
*/

#include "PrettyPrinter.h"

#include "BDictionary.h"
#include "BInteger.h"
#include "BList.h"
#include "BString.h"
#include "Utils.h"

namespace bencoding {

/**
* @brief Constructs a printer.
*/
PrettyPrinter::PrettyPrinter() = default;

/**
* @brief Creates a new printer.
*/
std::unique_ptr<PrettyPrinter> PrettyPrinter::create() {
	return std::unique_ptr<PrettyPrinter>(new PrettyPrinter());
}

/**
* @brief Returns a pretty representation of @a data.
*/
std::string PrettyPrinter::getPrettyRepr(std::shared_ptr<BItem> data) {
	prettyRepr.clear();
	data->accept(this);
	return prettyRepr;
}

void PrettyPrinter::visit(BDictionary *bDictionary) {
	//
	// Format:
	//
	//    {"key1": value1, "key2": value2, ...}
	//
	prettyRepr += "{";
	bool putComma = false;
	for (auto &item : *bDictionary) {
		if (putComma) {
			prettyRepr += ", ";
		}
		item.first->accept(this);
		prettyRepr += ": ";
		item.second->accept(this);
		putComma = true;
	}
	prettyRepr += "}";
}

void PrettyPrinter::visit(BInteger *bInteger) {
	//
	// Format:
	//
	//     int
	//
	prettyRepr += std::to_string(bInteger->value());
}

void PrettyPrinter::visit(BList *bList) {
	//
	// Format:
	//
	//     [item1, item2, ...]
	//
	prettyRepr += "[";
	bool putComma = false;
	for (auto bItem : *bList) {
		if (putComma) {
			prettyRepr += ", ";
		}
		bItem->accept(this);
		putComma = true;
	}
	prettyRepr += "]";
}

void PrettyPrinter::visit(BString *bString) {
	//
	// Format:
	//
	//     "string"
	//
	// We have to put a backslash before quotes, i.e. replace " with \".
	prettyRepr += '"' + replace(bString->value(), '"', std::string(R"(\")")) + '"';
}

/**
* @brief Returns a pretty representation of @a data.
*
* This function can be handy if you just want to pretty-print data without
* explicitly creating a pretty printer and calling @c encode() on it.
*
* See PrettyPrinter::getPrettyRepr() for more details.
*/
std::string getPrettyRepr(std::shared_ptr<BItem> data) {
	auto prettyPrinter = PrettyPrinter::create();
	return prettyPrinter->getPrettyRepr(data);
}

} // namespace bencoding
