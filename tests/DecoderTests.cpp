/**
* @file      DecoderTests.cpp
* @copyright (c) 2014 by Petr Zemek (s3rvac@gmail.com) and contributors
* @license   BSD, see the @c LICENSE file for more details
* @brief     Tests for the Decoder class.
*/

#include <memory>
#include <sstream>

#include <gtest/gtest.h>

#include "BInteger.h"
#include "BString.h"
#include "Decoder.h"
#include "TestUtils.h"

namespace bencoding {
namespace tests {

using namespace testing;

class DecoderTests: public Test {
protected:
	DecoderTests(): decoder(Decoder::create()) {}

	template <typename T>
	void assertDecodedAs(std::shared_ptr<BItem> bItem);

protected:
	std::unique_ptr<Decoder> decoder;
};

template <typename T>
void DecoderTests::assertDecodedAs(
		std::shared_ptr<BItem> bItem) {

	ASSERT_NE(bItem, nullptr)
		<< "expected a correctly decoded item";
	EXPECT_NE(bItem->as<T>(), nullptr)
		<< "expected " << typeid(T).name() << ", "
		<< "got " << typeid(*bItem).name();
}

//
// Integer decoding.
//

TEST_F(DecoderTests,
IntegerZeroIsCorrectlyDecoded) {
	std::string data("i0e");
	std::shared_ptr<BItem> bItem(decoder->decode(data));

	ADD_SCOPED_TRACE;
	assertDecodedAs<BInteger>(bItem);
	auto bInteger = bItem->as<BInteger>();
	EXPECT_EQ(0, bInteger->value());
}

TEST_F(DecoderTests,
PositiveIntegerIsCorrectlyDecoded) {
	std::shared_ptr<BItem> bItem(decoder->decode("i13e"));

	ADD_SCOPED_TRACE;
	assertDecodedAs<BInteger>(bItem);
	auto bInteger = bItem->as<BInteger>();
	EXPECT_EQ(13, bInteger->value());
}

TEST_F(DecoderTests,
ExplicitlyPositiveIntegerIsCorrectlyDecoded) {
	std::shared_ptr<BItem> bItem(decoder->decode("i+13e"));

	ADD_SCOPED_TRACE;
	assertDecodedAs<BInteger>(bItem);
	auto bInteger = bItem->as<BInteger>();
	EXPECT_EQ(+13, bInteger->value());
}

TEST_F(DecoderTests,
NegativeIntegerIsCorrectlyDecoded) {
	std::shared_ptr<BItem> bItem(decoder->decode("i-13e"));

	ADD_SCOPED_TRACE;
	assertDecodedAs<BInteger>(bItem);
	auto bInteger = bItem->as<BInteger>();
	EXPECT_EQ(-13, bInteger->value());
}

TEST_F(DecoderTests,
DecodeThrowsDecodingErrorWhenDecodingIntegerWithoutEndingE) {
	EXPECT_THROW(decoder->decode("i13"), DecodingError);
}

TEST_F(DecoderTests,
DecodeThrowsDecodingErrorWhenDecodingIntegerWithoutValue) {
	EXPECT_THROW(decoder->decode("ie"), DecodingError);
}

TEST_F(DecoderTests,
DecodeThrowsDecodingErrorWhenDecodingIntegerWithBeginningWhitespace) {
	EXPECT_THROW(decoder->decode("i 1e"), DecodingError);
}

TEST_F(DecoderTests,
DecodeThrowsDecodingErrorWhenDecodingIntegerWithTrailingWhitespace) {
	EXPECT_THROW(decoder->decode("i1 e"), DecodingError);
}

TEST_F(DecoderTests,
DecodeThrowsDecodingErrorWhenDecodingIntegerIsPaddedWithZeros) {
	// From https://wiki.theory.org/BitTorrentSpecification#Bencoding:
	//
	// "Only the significant digits should be used, one cannot pad the Integer
	//  with zeroes. such as i04e."
	//
	EXPECT_THROW(decoder->decode("i001e"), DecodingError);
}

TEST_F(DecoderTests,
DecodeThrowsDecodingErrorWhenDecodingIntegerOfInvalidValue) {
	EXPECT_THROW(decoder->decode("i e"), DecodingError);
	EXPECT_THROW(decoder->decode("i+e"), DecodingError);
	EXPECT_THROW(decoder->decode("i-e"), DecodingError);
	EXPECT_THROW(decoder->decode("i1-e"), DecodingError);
	EXPECT_THROW(decoder->decode("i1+e"), DecodingError);
	EXPECT_THROW(decoder->decode("i$e"), DecodingError);
	EXPECT_THROW(decoder->decode("i1.1e"), DecodingError);
}

//
// String decoding.
//

TEST_F(DecoderTests,
EmptyStringIsCorrrectlyDecoded) {
	std::string data("0:");
	std::shared_ptr<BItem> bItem(decoder->decode(data));

	ADD_SCOPED_TRACE;
	assertDecodedAs<BString>(bItem);
	auto bString = bItem->as<BString>();
	EXPECT_EQ("", bString->value());
}

TEST_F(DecoderTests,
NonemptyStringWithSingleCharacterIsCorrrectlyDecoded) {
	std::string data("1:a");
	std::shared_ptr<BItem> bItem(decoder->decode(data));

	ADD_SCOPED_TRACE;
	assertDecodedAs<BString>(bItem);
	auto bString = bItem->as<BString>();
	EXPECT_EQ("a", bString->value());
}

TEST_F(DecoderTests,
NonemptyStringWithTenCharacterIsCorrrectlyDecoded) {
	std::string data("10:abcdefghij");
	std::shared_ptr<BItem> bItem(decoder->decode(data));

	ADD_SCOPED_TRACE;
	assertDecodedAs<BString>(bItem);
	auto bString = bItem->as<BString>();
	EXPECT_EQ("abcdefghij", bString->value());
}

TEST_F(DecoderTests,
DecodeThrowsDecodingErrorWhenColonIsMissingInString) {
	EXPECT_THROW(decoder->decode("1a"), DecodingError);
}

TEST_F(DecoderTests,
DecodeThrowsDecodingErrorWhenStringHasNotEnoughCharacters) {
	EXPECT_THROW(decoder->decode("3:aa"), DecodingError);
}

//
// Other.
//

TEST_F(DecoderTests,
DecodeThrowsDecodingErrorWhenInputIsEmpty) {
	EXPECT_THROW(decoder->decode(""), DecodingError);
}

TEST_F(DecoderTests,
DecodeThrowsDecodingErrorWhenInputIsAtEnd) {
	std::istringstream input("");
	EXPECT_THROW(decoder->decode(input), DecodingError);
}

TEST_F(DecoderTests,
DecodeThrowsDecodingErrorWhenInputBeginsWithInvalidSymbol) {
	EXPECT_THROW(decoder->decode("$"), DecodingError);
}

TEST_F(DecoderTests,
DecodeThrowsDecodingErrorWhenInputBeginsWithUnexpectedSymbol) {
	EXPECT_THROW(decoder->decode("e"), DecodingError);
}

TEST_F(DecoderTests,
DecodeForStringThrowsDecodingErrorWhenInputIsNotCompletelyRead) {
	// Only the first i1e should be decoded, thus leaving i2e unread (such an
	// input is invalid as the integers are not inside of a list).
	EXPECT_THROW(decoder->decode("i1ei2e"), DecodingError);
}

TEST_F(DecoderTests,
DecodeFromStreamWorksAsDecodeFromString) {
	std::istringstream input("i0e");
	std::shared_ptr<BItem> bItem(decoder->decode(input));

	ADD_SCOPED_TRACE;
	assertDecodedAs<BInteger>(bItem);
	auto bInteger = bItem->as<BInteger>();
	EXPECT_EQ(0, bInteger->value());
}

TEST_F(DecoderTests,
DecodeFunctionForStringWorksAsCreatingDecoderAndCallingDecode) {
	std::string input("i0e");
	std::shared_ptr<BItem> bItem(decode(input));

	ADD_SCOPED_TRACE;
	assertDecodedAs<BInteger>(bItem);
	auto bInteger = bItem->as<BInteger>();
	EXPECT_EQ(0, bInteger->value());
}

TEST_F(DecoderTests,
DecodeFunctionForStreamWorksAsCreatingDecoderAndCallingDecode) {
	std::istringstream input("i0e");
	std::shared_ptr<BItem> bItem(decode(input));

	ADD_SCOPED_TRACE;
	assertDecodedAs<BInteger>(bItem);
	auto bInteger = bItem->as<BInteger>();
	EXPECT_EQ(0, bInteger->value());
}

} // namespace tests
} // namespace bencoding
