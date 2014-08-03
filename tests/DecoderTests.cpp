/**
* @file      DecoderTests.cpp
* @copyright (c) 2014 by Petr Zemek (s3rvac@gmail.com) and contributors
* @license   BSD, see the @c LICENSE file for more details
* @brief     Tests for the Decoder class.
*/

#include <memory>

#include <gtest/gtest.h>

#include "BInteger.h"
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
	ASSERT_NE(bItem->as<T>(), nullptr)
		<< "expected " << typeid(T).name() << ", "
		<< "got " << typeid(*bItem).name();
}

TEST_F(DecoderTests,
IntegerZeroIsCorrectlyDecoded) {
	std::shared_ptr<BItem> bItem{decoder->decode("i0e")};

	ADD_SCOPED_TRACE;
	assertDecodedAs<BInteger>(bItem);
	auto bInteger = bItem->as<BInteger>();
	ASSERT_EQ(0, bInteger->value());
}

} // namespace tests
} // namespace bencoding
