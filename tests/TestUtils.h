/**
* @file      TestUtils.h
* @copyright (c) 2014 by Petr Zemek (s3rvac@gmail.com) and contributors
* @license   BSD, see the @c LICENSE file for more details
* @brief     Test utilities.
*/

#ifndef BENCODING_TEST_UTILS_H
#define BENCODING_TEST_UTILS_H

#include <istream>
#include <string>

#include <gtest/gtest.h>

/**
* @brief Adds a SCOPED_TRACE from Google Test with a message containing the
*        test's name.
*/
#define ADD_SCOPED_TRACE \
	SCOPED_TRACE( \
		testing::UnitTest::GetInstance()->current_test_info()->test_case_name() + \
		std::string(".") + \
		testing::UnitTest::GetInstance()->current_test_info()->name() \
	)

namespace bencoding {
namespace tests {

void putIntoErrorState(std::istream &stream);
void putIntoEOFState(std::istream &stream);

} // namespace tests
} // namespace bencoding

#endif
