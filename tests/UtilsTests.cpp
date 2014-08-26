/**
* @file      UtilsTests.cpp
* @copyright (c) 2014 by Petr Zemek (s3rvac@gmail.com) and contributors
* @license   BSD, see the @c LICENSE file for more details
* @brief     Tests for the utilities.
*/

#include <gtest/gtest.h>

#include "TestUtils.h"
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
	EXPECT_FALSE(dataReadCorrectly);
}

TEST_F(UtilsTests,
ReadUpToStoresReadCharsEvenWhenSentinelIsNotFound) {
	std::istringstream input("abcd");
	std::string readData;

	readUpTo(input, readData, '$');
	EXPECT_EQ("abcd", readData);
}

TEST_F(UtilsTests,
ReadUpToReturnsFalseWhenInputIsInError) {
	std::istringstream input("abcd$");
	std::string readData;

	putIntoErrorState(input);
	EXPECT_FALSE(readUpTo(input, readData, '$'));
}

TEST_F(UtilsTests,
ReadUpToDoesNotReadAnyDataWhenInputIsInError) {
	std::istringstream input("abc$");
	std::string readData;

	putIntoErrorState(input);
	readUpTo(input, readData, '$');
	EXPECT_EQ("", readData);
}

TEST_F(UtilsTests,
ReadUpToReturnsFalseWhenInputIsAtEOF) {
	std::istringstream input("abcd$");
	std::string readData;

	putIntoEOFState(input);
	EXPECT_FALSE(readUpTo(input, readData, '$'));
}

TEST_F(UtilsTests,
ReadUpToDoesNotReadAnyDataWhenInputIsAtEOF) {
	std::istringstream input("abcd$");
	std::string readData;

	putIntoEOFState(input);
	readUpTo(input, readData, '$');
	EXPECT_EQ("", readData);
}

//
// readUntil()
//

TEST_F(UtilsTests,
ReadUntilReadsCorrectlyAllCharactersIncludingLast) {
	std::istringstream input("abcd$");
	std::string readData;

	bool dataReadCorrectly = readUntil(input, readData, '$');
	ASSERT_TRUE(dataReadCorrectly);
	EXPECT_EQ(readData, "abcd$");
}

TEST_F(UtilsTests,
ReadUntilToReturnsFalseWhenLastIsNotFound) {
	std::istringstream input("abcd");
	std::string readData;

	bool dataReadCorrectly = readUntil(input, readData, '$');
	EXPECT_FALSE(dataReadCorrectly);
}

TEST_F(UtilsTests,
ReadUntilStoresReadCharsEvenWhenLastIsNotFound) {
	std::istringstream input("abcd");
	std::string readData;

	readUntil(input, readData, '$');
	EXPECT_EQ("abcd", readData);
}

TEST_F(UtilsTests,
ReadUntilDoesNotReadAnyDataWhenInputIsInError) {
	std::istringstream input("abcd$");
	std::string readData;

	putIntoErrorState(input);
	readUntil(input, readData, '$');
	EXPECT_EQ("", readData);
}

TEST_F(UtilsTests,
ReadUntilReturnsFalseWhenInputIsAtEOF) {
	std::istringstream input("abc$");
	std::string readData;

	putIntoEOFState(input);
	EXPECT_FALSE(readUntil(input, readData, '$'));
}

TEST_F(UtilsTests,
ReadUntilDoesNotReadAnyDataWhenInputIsAtEOF) {
	std::istringstream input("abcd$");
	std::string readData;

	putIntoEOFState(input);
	readUntil(input, readData, '$');
	EXPECT_EQ("", readData);
}

//
// replace()
//

TEST_F(UtilsTests,
ReplaceDoesNotPerformAnyReplacementWhenStringIsEmpty) {
	EXPECT_EQ("", replace("", 'x', "X"));
}

TEST_F(UtilsTests,
ReplaceDoesNotPerformAnyReplacementWhenCharDoesNotAppearInString) {
	EXPECT_EQ("abcd", replace("abcd", 'x', "X"));
}

TEST_F(UtilsTests,
ReplaceCorrectlyReplacesCharInStringIfItOccursOnce) {
	EXPECT_EQ("Abcd", replace("abcd", 'a', "A"));
}

TEST_F(UtilsTests,
ReplaceCorrectlyReplacesCharInStringIfItOccursTwice) {
	EXPECT_EQ("AbcA", replace("abca", 'a', "A"));
}

TEST_F(UtilsTests,
ReplaceCorrectlyReplacesCharInStringWhenWithWhatIsLongerThanOneChar) {
	EXPECT_EQ("XXXXbcXXXX", replace("abca", 'a', "XXXX"));
}

TEST_F(UtilsTests,
ReplaceDeletesCharsInStringWhenWithWhatIsEmpty) {
	EXPECT_EQ("bc", replace("abca", 'a', ""));
}

} // namespace tests
} // namespace bencoding
