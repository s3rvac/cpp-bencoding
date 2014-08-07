/**
* @file      BIntegerTests.cpp
* @copyright (c) 2014 by Petr Zemek (s3rvac@gmail.com) and contributors
* @license   BSD, see the @c LICENSE file for more details
* @brief     Tests for the BInteger class.
*/

#include <gtest/gtest.h>

#include "BInteger.h"

namespace bencoding {
namespace tests {

using namespace testing;

class BIntegerTests: public Test {};

TEST_F(BIntegerTests,
ValueReturnsCorrectValueAfterCreation) {
	auto i = BInteger::create(5);

	EXPECT_EQ(5, i->value());
}

TEST_F(BIntegerTests,
ValueReturnsCorrectValueAfterSet) {
	auto i = BInteger::create(5);
	i->setValue(10);

	EXPECT_EQ(10, i->value());
}

} // namespace tests
} // namespace bencoding
