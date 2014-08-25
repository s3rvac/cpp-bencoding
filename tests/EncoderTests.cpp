/**
* @file      EncoderTests.cpp
* @copyright (c) 2014 by Petr Zemek (s3rvac@gmail.com) and contributors
* @license   BSD, see the @c LICENSE file for more details
* @brief     Tests for the Encoder class.
*/

#include <gtest/gtest.h>

#include "BDictionary.h"
#include "BInteger.h"
#include "BList.h"
#include "BString.h"
#include "Encoder.h"

namespace bencoding {
namespace tests {

using namespace testing;

class EncoderTests: public Test {
protected:
	EncoderTests(): encoder(Encoder::create()) {}

protected:
	std::unique_ptr<Encoder> encoder;
};

//
// Dictionary encoding.
//

TEST_F(EncoderTests,
EmptyDictionarysIsCorrectlyEncoded) {
	std::shared_ptr<BDictionary> bDictionary(BDictionary::create());

	EXPECT_EQ("de", encoder->encode(bDictionary));
}

TEST_F(EncoderTests,
DictionarysWithOneItemIsCorrectlyEncoded) {
	std::shared_ptr<BDictionary> bDictionary(BDictionary::create());
	(*bDictionary)[BString::create("test")] = BInteger::create(1);

	EXPECT_EQ("d4:testi1ee", encoder->encode(bDictionary));
}

TEST_F(EncoderTests,
DictionarysWithTwoItemsIsCorrectlyEncoded) {
	std::shared_ptr<BDictionary> bDictionary(BDictionary::create());
	(*bDictionary)[BString::create("test1")] = BInteger::create(1);
	(*bDictionary)[BString::create("test2")] = BInteger::create(2);

	EXPECT_EQ("d5:test1i1e5:test2i2ee", encoder->encode(bDictionary));
}

//
// Integer encoding.
//

TEST_F(EncoderTests,
IntegerWithZeroValueIsCorrectlyEncoded) {
	std::shared_ptr<BItem> data(BInteger::create(0));

	EXPECT_EQ("i0e", encoder->encode(data));
}

TEST_F(EncoderTests,
IntegerWithPositiveValueIsCorrectlyEncoded) {
	std::shared_ptr<BItem> data(BInteger::create(13));

	EXPECT_EQ("i13e", encoder->encode(data));
}

TEST_F(EncoderTests,
IntegerWithNegativeValueIsCorrectlyEncoded) {
	std::shared_ptr<BItem> data(BInteger::create(-13));

	EXPECT_EQ("i-13e", encoder->encode(data));
}

//
// List encoding.
//

TEST_F(EncoderTests,
EmptyListIsEncodedCorrectly) {
	std::shared_ptr<BList> bList = BList::create();

	EXPECT_EQ("le", encoder->encode(bList));
}

TEST_F(EncoderTests,
ListContainingTwoStringsIsEncodedCorrectly) {
	std::shared_ptr<BList> bList = BList::create();
	bList->push_back(BString::create("test"));
	bList->push_back(BString::create("hello"));

	EXPECT_EQ("l4:test5:helloe", encoder->encode(bList));
}

//
// String encoding.
//

TEST_F(EncoderTests,
EmptyStringIsCorrectlyEncoded) {
	std::shared_ptr<BItem> data(BString::create(""));

	EXPECT_EQ("0:", encoder->encode(data));
}

TEST_F(EncoderTests,
NonemptyStringIsCorrectlyEncoded) {
	std::shared_ptr<BItem> data(BString::create("test"));

	EXPECT_EQ("4:test", encoder->encode(data));
}

//
// Other.
//

TEST_F(EncoderTests,
EncodeFunctionWorksAsCreatingEncoderAndCallingEncode) {
	std::shared_ptr<BItem> data(BInteger::create(0));

	EXPECT_EQ("i0e", encode(data));
}

} // namespace tests
} // namespace bencoding
