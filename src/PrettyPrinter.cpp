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
*
* @param[in] data Data to return a pretty representation for.
* @param[in] indent A single level of indentation.
*
* Use getPrettyReprWithoutIndent() if you want to get a pretty representation
* without any indentation.
*/
std::string PrettyPrinter::getPrettyRepr(std::shared_ptr<BItem> data,
		const std::string &indent) {
	prettyRepr.clear();
	indentLevel = indent;
	currentIndent.clear();
	this->indent = true;
	data->accept(this);
	return prettyRepr;
}

/**
* @brief Returns a pretty representation of @a data without any indentation.
*
* @param[in] data Data to return a pretty representation for.
* @param[in] indent A single level of indentation.
*
* Use getPrettyRepr() if you want to get a pretty representation with
* indentation.
*/
std::string PrettyPrinter::getPrettyReprWithoutIndent(std::shared_ptr<BItem> data) {
	prettyRepr.clear();
	indent = false;
	data->accept(this);
	return prettyRepr;
}

/**
* @brief Stores the current indentation into @c prettyRepr.
*/
void PrettyPrinter::storeCurrentIndent() {
	prettyRepr += currentIndent;
}

/**
* @brief Increases the current indentation by a single level.
*/
void PrettyPrinter::increaseIndentLevel() {
	currentIndent += indentLevel;
}

/**
* @brief Decreases the current indentation by a single level.
*/
void PrettyPrinter::decreaseIndentLevel() {
	currentIndent = currentIndent.substr(0,
		currentIndent.size() - indentLevel.size());
}

void PrettyPrinter::visit(BDictionary *bDictionary) {
	if (indent) {
		formatAndStoreWithIndent(bDictionary);
	} else {
		formatAndStoreWithoutIndent(bDictionary);
	}
}

void PrettyPrinter::visit(BInteger *bInteger) {
	formatAndStore(bInteger);
}

void PrettyPrinter::visit(BList *bList) {
	if (indent) {
		formatAndStoreWithIndent(bList);
	} else {
		formatAndStoreWithoutIndent(bList);
	}
}

void PrettyPrinter::visit(BString *bString) {
	formatAndStore(bString);
}

/**
* @brief Formats @a bDictionary with an indentation and stores it into @c
*        prettyRepr.
*/
void PrettyPrinter::formatAndStoreWithIndent(BDictionary *bDictionary) {
	//
	// Format:
	//
	//    {
	//        "key1": value1,
	//        "key2": value2,
	//        ...
	//    }
	//
	prettyRepr += "{\n";
	increaseIndentLevel();
	bool putComma = false;
	for (auto &item : *bDictionary) {
		if (putComma) {
			prettyRepr += ",\n";
		}
		storeCurrentIndent();
		item.first->accept(this);
		prettyRepr += ": ";
		item.second->accept(this);
		putComma = true;
	}
	if (!bDictionary->empty()) {
		prettyRepr += "\n";
	}
	decreaseIndentLevel();
	storeCurrentIndent();
	prettyRepr += "}";
}

/**
* @brief Formats @a bDictionary without an indentation and stores it into @c
*        prettyRepr.
*/
void PrettyPrinter::formatAndStoreWithoutIndent(BDictionary *bDictionary) {
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

/**
* @brief Formats @a bInteger and stores it into @c prettyRepr.
*/
void PrettyPrinter::formatAndStore(BInteger *bInteger) {
	//
	// Format (the same with and without indentation):
	//
	//     int
	//
	prettyRepr += std::to_string(bInteger->value());
}

/**
* @brief Formats @a bList with an indentation and stores it into @c
*        prettyRepr.
*/
void PrettyPrinter::formatAndStoreWithIndent(BList *bList) {
	//
	// Format:
	//
	//     [
	//         item1,
	//         item2,
	//         ...
	//     ]
	//
	prettyRepr += "[\n";
	increaseIndentLevel();
	bool putComma = false;
	for (auto bItem : *bList) {
		if (putComma) {
			prettyRepr += ",\n";
		}
		storeCurrentIndent();
		bItem->accept(this);
		putComma = true;
	}
	if (!bList->empty()) {
		prettyRepr += "\n";
	}
	decreaseIndentLevel();
	storeCurrentIndent();
	prettyRepr += "]";
}

/**
* @brief Formats @a bList without an indentation and stores it into @c
*        prettyRepr.
*/
void PrettyPrinter::formatAndStoreWithoutIndent(BList *bList) {
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

/**
* @brief Formats @a bString and stores it into @c prettyRepr.
*/
void PrettyPrinter::formatAndStore(BString *bString) {
	//
	// Format (the same with and without indentation):
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
std::string getPrettyRepr(std::shared_ptr<BItem> data,
		const std::string &indent) {
	auto prettyPrinter = PrettyPrinter::create();
	return prettyPrinter->getPrettyRepr(data, indent);
}

/**
* @brief Returns a pretty representation of @a data without any indentation.
*
* This function can be handy if you just want to pretty-print data without
* explicitly creating a pretty printer and calling @c encode() on it.
*
* See PrettyPrinter::getPrettyReprWithoutIndent() for more details.
*/
std::string getPrettyReprWithoutIndent(std::shared_ptr<BItem> data) {
	auto prettyPrinter = PrettyPrinter::create();
	return prettyPrinter->getPrettyReprWithoutIndent(data);
}

} // namespace bencoding
