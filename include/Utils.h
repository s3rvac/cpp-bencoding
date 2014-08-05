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
#include <sstream>
#include <string>

namespace bencoding {

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

bool readUntil(std::istream &stream, std::string &readData, char sentinel);

} // namespace bencoding

#endif
