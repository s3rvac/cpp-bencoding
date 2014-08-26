/**
* @file      BDictionary.cpp
* @copyright (c) 2014 by Petr Zemek (s3rvac@gmail.com) and contributors
* @license   BSD, see the @c LICENSE file for more details
* @brief     Implementation of the BDictionary class.
*/

#include "BDictionary.h"

#include <cassert>

#include "BItemVisitor.h"
#include "BString.h"

namespace bencoding {

/**
* @brief Checks if <tt>lhs->value() < rhs->value()</tt>.
*
* @return @c true if <tt>lhs->value() < rhs->value()</tt>, @c false otherwise.
*/
bool BDictionary::BStringByValueComparator::operator()(
		const std::shared_ptr<BString> &lhs,
		const std::shared_ptr<BString> &rhs) const {
	return lhs->value() < rhs->value();
}

/**
* @brief Constructs an empty dictionary.
*/
BDictionary::BDictionary() = default;

/**
* @brief Constructs a dictionary from the given items.
*/
BDictionary::BDictionary(std::initializer_list<value_type> items):
	itemMap(items) {}

/**
* @brief Creates and returns a new dictionary.
*/
std::unique_ptr<BDictionary> BDictionary::create() {
	return std::unique_ptr<BDictionary>(new BDictionary());
}

/**
* @brief Creates and returns a new dictionary containing the given @a items.
*/
std::unique_ptr<BDictionary> BDictionary::create(
		std::initializer_list<value_type> items) {
	return std::unique_ptr<BDictionary>(new BDictionary(items));
}

/**
* @brief Returns the number of items in the dictionary.
*/
BDictionary::size_type BDictionary::size() const {
	return itemMap.size();
}

/**
* @brief Checks if the dictionary is empty.
*
* @return @c true if the dictionary is empty, @c false otherwise.
*/
bool BDictionary::empty() const {
	return itemMap.empty();
}

/**
* @brief Accesses the specified element.
*
* @returns A reference to the value that is mapped to a key equivalent to key.
*
* If there is no value mapped to @a key, an insertion of a null pointer is
* automatically performed, and a reference to this null pointer is returned.
*/
BDictionary::mapped_type &BDictionary::operator[](const key_type &key) {
	return itemMap[key];
}

/**
* @brief Returns an iterator to the beginning of the dictionary.
*/
BDictionary::iterator BDictionary::begin() {
	return itemMap.begin();
}

/**
* @brief Returns an iterator to the end of the dictionary.
*/
BDictionary::iterator BDictionary::end() {
	return itemMap.end();
}

/**
* @brief Returns a constant iterator to the beginning of the dictionary.
*/
BDictionary::const_iterator BDictionary::begin() const {
	return itemMap.begin();
}

/**
* @brief Returns a constant iterator to the end of the dictionary.
*/
BDictionary::const_iterator BDictionary::end() const {
	return itemMap.end();
}

/**
* @brief Returns a constant iterator to the beginning of the dictionary.
*/
BDictionary::const_iterator BDictionary::cbegin() const {
	return itemMap.cbegin();
}

/**
* @brief Returns a constant iterator to the end of the dictionary.
*/
BDictionary::const_iterator BDictionary::cend() const {
	return itemMap.cend();
}

void BDictionary::accept(BItemVisitor *visitor) {
	visitor->visit(this);
}

} // namespace bencoding
