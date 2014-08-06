/**
* @file      Utils.cpp
* @copyright (c) 2014 by Petr Zemek (s3rvac@gmail.com) and contributors
* @license   BSD, see the @c LICENSE file for more details
* @brief     Implementation of the utilities.
*/

#include "Utils.h"

namespace bencoding {

/**
* @brief Reads data from the given @a stream up to @a sentinel, which is left
*        in @a stream.
*
* @param[in] stream Stream from which the data are read.
* @param[out] readData String into which the read data are stored.
* @param[in] sentinel The data are up to this character.
*
* @return @c true if all the data were read correctly up to @a sentinel, @c
*         false otherwise.
*
* @a sentinel is not read and is kept in the stream. If @a sentinel is not
* found during the reading, this function returns @c false. Read data are
* appended into @a readData.
*/
bool readUpTo(std::istream &stream, std::string &readData, char sentinel) {
	// Do not use std::getline() because it eats the sentinel from the stream.
	while (stream.peek() != std::char_traits<char>::eof() &&
			stream.peek() != sentinel) {
		readData += stream.get();
	}
	return stream && stream.peek() == sentinel;
}

} // namespace bencoding
