/**
* @file      BStringTests.cpp
* @copyright (c) 2014 by Petr Zemek (s3rvac@gmail.com) and contributors
* @license   BSD, see the @c LICENSE file for more details
* @brief     Tests for the BString class.
*/

#include <gtest/gtest.h>

#include "BString.h"

namespace bencoding {
namespace tests {

using namespace testing;

class BStringTests: public Test {};

TEST_F(BStringTests,
ValueReturnsCorrectValueAfterCreation) {
	auto s = BString::create("test");

	EXPECT_EQ("test", s->value());
}

TEST_F(BStringTests,
ValueReturnsCorrectValueAfterSet) {
	auto s = BString::create("test");
	s->setValue("other");

	EXPECT_EQ("other", s->value());
}

TEST_F(BStringTests,
LengthReturnsCorrectValue) {
	auto s = BString::create("test");

	EXPECT_EQ(4, s->length());
}

} // namespace tests
} // namespace bencoding
