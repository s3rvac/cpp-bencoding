/**
* @file      BInteger.cpp
* @copyright (c) 2014 by Petr Zemek (s3rvac@gmail.com) and contributors
* @license   BSD, see the @c LICENSE file for more details
* @brief     Implementation of the BInteger class.
*/

#include "BInteger.h"

namespace bencoding {

/**
* @brief Constructs the integer with the given @a value.
*/
BInteger::BInteger(ValueType value): _value(value) {}

/**
* @brief Creates and returns a new integer.
*/
std::unique_ptr<BInteger> BInteger::create(ValueType value) {
	return std::unique_ptr<BInteger>(new BInteger(value));
}

/**
* @brief Returns the integer's value.
*/
auto BInteger::value() const -> ValueType {
	return _value;
}

/**
* @brief Sets a new value.
*/
void BInteger::setValue(ValueType value) {
	_value = value;
}

} // namespace bencoding
