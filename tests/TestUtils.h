/**
* @file      TestUtils.h
* @copyright (c) 2014 by Petr Zemek (s3rvac@gmail.com) and contributors
* @license   BSD, see the @c LICENSE file for more details
* @brief     Test utilities.
*/

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
