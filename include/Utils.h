/**
* @file      Utils.h
* @copyright (c) 2014 by Petr Zemek (s3rvac@gmail.com) and contributors
* @license   BSD, see the @c LICENSE file for more details
* @brief     Utilities.
*/

#ifndef BENCODING_UTILS_H
#define BENCODING_UTILS_H

#include <ios>
#include <istream>
#include <queue>
#include <sstream>
#include <stack>
#include <string>

namespace bencoding {

/// @name Conversions
/// @{

/**
* @brief Converts the given string into a number
*
* @param[in] str String to be converted into a number.
* @param[out] num Place to store the converted number.
* @param[in] format Number format (e.g. std::dec or std::hex).
*
* @return @c true if the conversion was successful, @c false otherwise.
*
* If the conversion fails, @a num is left unchanged.
*/
template<typename N>
bool strToNum(const std::string &str, N &num,
		std::ios_base &(* format)(std::ios_base &) = std::dec) {
	std::istringstream stream(str);
	N convNum = 0;
	stream >> format >> convNum;
	if (!stream.fail() && stream.eof()) {
		num = convNum;
		return true;
	}
	return false;
}

/// @}

/// @name Data Reading
/// @{

bool readUpTo(std::istream &stream, std::string &readData, char sentinel);
bool readUntil(std::istream &stream, std::string &readData, char last);

/// @}

/// @name Container Operations
/// @{

/**
* @brief Clears the given container.
*
* @tparam ContainerType Type of the container.
*/
template <class ContainerType>
void clear(ContainerType &container) {
	container.clear();
}

/**
* @brief A "specialization" of clear<>() for std::queue.
*
* @tparam ItemType Type of the items in the queue.
*/
template <typename ItemType>
void clear(std::queue<ItemType> &queue) {
	// std::queue doesn't provide the clear() member function, so we have to
	// clear it manually.
	while (!queue.empty()) {
		queue.pop();
	}
}

/**
* @brief A "specialization" of clear<>() for std::stack.
*
* @tparam ItemType Type of the items in the stack.
*/
template <typename ItemType>
void clear(std::stack<ItemType> &stack) {
	// std::stack doesn't provide the clear() member function, so we have to
	// clear it manually.
	while (!stack.empty()) {
		stack.pop();
	}
}

/// @}

} // namespace bencoding

#endif
