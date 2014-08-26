/**
* @file      DecoderTests.cpp
* @copyright (c) 2014 by Petr Zemek (s3rvac@gmail.com) and contributors
* @license   BSD, see the @c LICENSE file for more details
* @brief     Tests for the Decoder class.
*/

#include <memory>
#include <sstream>

#include <gtest/gtest.h>

#include "BDictionary.h"
#include "BInteger.h"
#include "BList.h"
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
// Dictionary decoding.
//

TEST_F(DecoderTests,
EmptyDictionaryIsDecodedCorrectly) {
	std::string data("de");
	std::shared_ptr<BItem> bItem(decoder->decode(data));

	ADD_SCOPED_TRACE;
	assertDecodedAs<BDictionary>(bItem);
	auto bDictionary = bItem->as<BDictionary>();
	EXPECT_TRUE(bDictionary->empty());
}

TEST_F(DecoderTests,
DictionaryWithSingleItemIsDecodedCorrectly) {
	std::string data("d4:testi1ee");
	std::shared_ptr<BItem> bItem(decoder->decode(data));

	ADD_SCOPED_TRACE;
	assertDecodedAs<BDictionary>(bItem);
	auto bDictionary = bItem->as<BDictionary>();
	EXPECT_EQ(1, bDictionary->size());

	auto i = bDictionary->begin();
	assertDecodedAs<BString>(i->first);
	auto key = i->first->as<BString>();
	EXPECT_EQ("test", key->value());

	assertDecodedAs<BInteger>(i->second);
	auto value = i->second->as<BInteger>();
	EXPECT_EQ(1, value->value());
}

TEST_F(DecoderTests,
DictionaryWithTwoItemsIsDecodedCorrectly) {
	std::string data("d5:test1i1e5:test2i2ee");
	std::shared_ptr<BItem> bItem(decoder->decode(data));

	ADD_SCOPED_TRACE;
	assertDecodedAs<BDictionary>(bItem);
	auto bDictionary = bItem->as<BDictionary>();
	EXPECT_EQ(2, bDictionary->size());

	auto i = bDictionary->begin();
	assertDecodedAs<BString>(i->first);
	auto key1 = i->first->as<BString>();
	EXPECT_EQ("test1", key1->value());

	assertDecodedAs<BInteger>(i->second);
	auto value1 = i->second->as<BInteger>();
	EXPECT_EQ(1, value1->value());

	++i;
	assertDecodedAs<BString>(i->first);
	auto key2 = i->first->as<BString>();
	EXPECT_EQ("test2", key2->value());

	assertDecodedAs<BInteger>(i->second);
	auto value2 = i->second->as<BInteger>();
	EXPECT_EQ(2, value2->value());
}

TEST_F(DecoderTests,
DictionaryWithKeysThatAreNotSortedIsDecodedCorrectly) {
	// Even though the specification says that a dictionary has all its keys
	// lexicographically sorted, we support the decoding of dictionaries whose
	// keys are not sorted. The resulting dictionary, however, will always have
	// its keys sorted to conform to the specification.
	std::string data("d1:bi2e1:ai1ee");
	std::shared_ptr<BItem> bItem(decoder->decode(data));

	ADD_SCOPED_TRACE;
	assertDecodedAs<BDictionary>(bItem);
	auto bDictionary = bItem->as<BDictionary>();
	EXPECT_EQ(2, bDictionary->size());

	auto i = bDictionary->begin();
	assertDecodedAs<BString>(i->first);
	auto key1 = i->first->as<BString>();
	EXPECT_EQ("a", key1->value());

	assertDecodedAs<BInteger>(i->second);
	auto value1 = i->second->as<BInteger>();
	EXPECT_EQ(1, value1->value());

	++i;
	assertDecodedAs<BString>(i->first);
	auto key2 = i->first->as<BString>();
	EXPECT_EQ("b", key2->value());

	assertDecodedAs<BInteger>(i->second);
	auto value2 = i->second->as<BInteger>();
	EXPECT_EQ(2, value2->value());
}

TEST_F(DecoderTests,
DecodeThrowsDecodingErrorWhenDecodingDictionaryWithoutEndingE) {
	EXPECT_THROW(decoder->decode("d"), DecodingError);
}

TEST_F(DecoderTests,
DecodeThrowsDecodingErrorWhenDecodingDictionaryWithKeyNotBeingString) {
	EXPECT_THROW(decoder->decode("di1ei2ee"), DecodingError);
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
// List decoding.
//

TEST_F(DecoderTests,
EmptyListIsCorrectlyDecoded) {
	std::string data("le");
	std::shared_ptr<BItem> bItem(decoder->decode(data));

	ADD_SCOPED_TRACE;
	assertDecodedAs<BList>(bItem);
	auto bList = bItem->as<BList>();
	EXPECT_TRUE(bList->empty());
}

TEST_F(DecoderTests,
ListWithSingleIntegerIsDecodedCorrectly) {
	std::string data("li1ee");
	std::shared_ptr<BItem> bItem(decoder->decode(data));

	ADD_SCOPED_TRACE;
	assertDecodedAs<BList>(bItem);
	auto bList = bItem->as<BList>();
	ASSERT_EQ(1, bList->size());
	auto firstItem = bList->front();
	assertDecodedAs<BInteger>(firstItem);
	auto firstItemAsInteger = firstItem->as<BInteger>();
	EXPECT_EQ(1, firstItemAsInteger->value());
}

TEST_F(DecoderTests,
ListWithTwoStringsIsDecodedCorrectly) {
	std::string data("l4:test5:helloe");
	std::shared_ptr<BItem> bItem(decoder->decode(data));

	ADD_SCOPED_TRACE;
	assertDecodedAs<BList>(bItem);
	auto bList = bItem->as<BList>();
	ASSERT_EQ(2, bList->size());
	// "test"
	auto firstItem = bList->front();
	assertDecodedAs<BString>(firstItem);
	auto firstItemAsString = firstItem->as<BString>();
	EXPECT_EQ("test", firstItemAsString->value());
	// "hello"
	auto secondItem = bList->back();
	assertDecodedAs<BString>(secondItem);
	auto secondItemAsString = secondItem->as<BString>();
	EXPECT_EQ("hello", secondItemAsString->value());
}

TEST_F(DecoderTests,
DecodeThrowsDecodingErrorWhenCharEIsMissingFromEndOfList) {
	EXPECT_THROW(decoder->decode("li1e"), DecodingError);
	EXPECT_THROW(decoder->decode("l4:test"), DecodingError);
}

TEST_F(DecoderTests,
DecodeThrowsDecodingErrorWhenListItemIsInvalidIsMissingFromEndOfList) {
	EXPECT_THROW(decoder->decode("l$e"), DecodingError);
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
DecodeThrowsDecodingErrorWhenInputIsAtEOF) {
	std::istringstream input;
	putIntoEOFState(input);

	EXPECT_THROW(decoder->decode(input), DecodingError);
}

TEST_F(DecoderTests,
DecodeThrowsDecodingErrorWhenInputIsInError) {
	std::istringstream input;
	putIntoErrorState(input);

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
DecodeForStreamDoesNotReadCharactersPassFirstDecodedItem) {
	// The second i2e is supposed to be left in the stream.
	std::istringstream input("i1ei2e");
	std::shared_ptr<BItem> bItem(decoder->decode(input));

	ASSERT_EQ('i', input.get());
	ASSERT_EQ('2', input.get());
	ASSERT_EQ('e', input.get());
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
