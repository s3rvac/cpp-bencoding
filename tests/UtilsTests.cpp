/**
* @file      UtilsTests.cpp
* @copyright (c) 2014 by Petr Zemek (s3rvac@gmail.com) and contributors
* @license   BSD, see the @c LICENSE file for more details
* @brief     Tests for the utilities.
*/

#include <gtest/gtest.h>

#include "Utils.h"

namespace bencoding {
namespace tests {

using namespace testing;

class UtilsTests: public Test {};

//
// strToNum()
//

TEST_F(UtilsTests,
StrToNumWithValidDecimalIntegerSucceeds) {
	int num = 0;
	EXPECT_TRUE(strToNum("-1000", num, std::dec));
	EXPECT_EQ(-1000, num);

	num = 0;
	EXPECT_TRUE(strToNum("-1", num, std::dec));
	EXPECT_EQ(-1, num);

	num = 0;
	EXPECT_TRUE(strToNum("0", num, std::dec));
	EXPECT_EQ(0, num);

	num = 0;
	EXPECT_TRUE(strToNum("1", num, std::dec));
	EXPECT_EQ(1, num);

	num = 0;
	EXPECT_TRUE(strToNum("1000", num, std::dec));
	EXPECT_EQ(1000, num);

	num = 0;
	EXPECT_TRUE(strToNum("0000", num, std::dec));
	EXPECT_EQ(0, num);

	num = 0;
	EXPECT_TRUE(strToNum("0003", num, std::dec));
	EXPECT_EQ(3, num);
}

TEST_F(UtilsTests,
StrToNumWithInvalidDecimalIntegerFails) {
	int num = -1;
	EXPECT_FALSE(strToNum("", num, std::dec));
	EXPECT_EQ(-1, num);

	num = -1;
	EXPECT_FALSE(strToNum("zzz", num, std::dec));
	EXPECT_EQ(-1, num);

	num = -1;
	EXPECT_FALSE(strToNum("13 something", num, std::dec));
	EXPECT_EQ(-1, num);

	num = -1;
	EXPECT_FALSE(strToNum("13something", num, std::dec));
	EXPECT_EQ(-1, num);
}

TEST_F(UtilsTests,
StrToNumWithValidHexadecimalIntegerSucceeds) {
	int num = 0;
	EXPECT_TRUE(strToNum("-0x3E8", num, std::hex));
	EXPECT_EQ(-0x3E8, num);

	num = 0;
	EXPECT_TRUE(strToNum("-0x1", num, std::hex));
	EXPECT_EQ(-0x1, num);

	num = 0;
	EXPECT_TRUE(strToNum("0x0", num, std::hex));
	EXPECT_EQ(0x0, num);

	num = 0;
	EXPECT_TRUE(strToNum("0x1", num, std::hex));
	EXPECT_EQ(0x1, num);

	num = 0;
	EXPECT_TRUE(strToNum("0x3E8", num, std::hex));
	EXPECT_EQ(0x3E8, num);

	num = 0;
	EXPECT_TRUE(strToNum("0x00C", num, std::hex));
	EXPECT_EQ(0x00C, num);
}

TEST_F(UtilsTests,
StrToNumWithInvalidHexadecimalIntegerFails) {
	int num = -1;
	EXPECT_FALSE(strToNum("", num, std::hex));
	EXPECT_EQ(-1, num);

	num = -1;
	EXPECT_FALSE(strToNum("0x", num, std::hex));
	EXPECT_EQ(-1, num);

	num = -1;
	EXPECT_FALSE(strToNum("zz", num, std::hex));
	EXPECT_EQ(-1, num);

	num = -1;
	EXPECT_FALSE(strToNum("0xC something", num, std::hex));
	EXPECT_EQ(-1, num);

	num = -1;
	EXPECT_FALSE(strToNum("0xCsomething", num, std::hex));
	EXPECT_EQ(-1, num);
}

//
// readUpTo()
//

TEST_F(UtilsTests,
ReadUpToReadsCorrectlyAllCharactersUpToSentinel) {
	std::istringstream input("abcd$");
	std::string readData;

	bool dataReadCorrectly = readUpTo(input, readData, '$');
	ASSERT_TRUE(dataReadCorrectly);
	EXPECT_EQ(readData, "abcd");
}

TEST_F(UtilsTests,
ReadUpToReturnsFalseWhenSentinelIsNotFound) {
	std::istringstream input("abcd");
	std::string readData;

	bool dataReadCorrectly = readUpTo(input, readData, '$');
	ASSERT_FALSE(dataReadCorrectly);
}

TEST_F(UtilsTests,
ReadUpToStoresReadCharsEvenWhenSentinelIsNotFound) {
	std::istringstream input("abcd");
	std::string readData;

	readUpTo(input, readData, '$');
	ASSERT_EQ("abcd", readData);
}

} // namespace tests
} // namespace bencoding
