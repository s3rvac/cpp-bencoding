/**
* @file      TestUtils.cpp
* @copyright (c) 2014 by Petr Zemek (s3rvac@gmail.com) and contributors
* @license   BSD, see the @c LICENSE file for more details
* @brief     Implementation of the test utilities.
*/

#include "TestUtils.h"

#include <ios>

namespace bencoding {
namespace tests {

/**
* @brief Puts @a stream into an error state.
*/
void putIntoErrorState(std::istream &stream) {
	stream.setstate(std::ios::badbit);
}

/**
* @brief Puts @a stream into an EOF state.
*/
void putIntoEOFState(std::istream &stream) {
	stream.setstate(std::ios::eofbit);
}

} // namespace tests
} // namespace bencoding
