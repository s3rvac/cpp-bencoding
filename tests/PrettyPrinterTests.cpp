/**
* @file      PrettyPrinterTests.cpp
* @copyright (c) 2014 by Petr Zemek (s3rvac@gmail.com) and contributors
* @license   BSD, see the @c LICENSE file for more details
* @brief     Tests for the PrettyPrinter class.
*/

#include <gtest/gtest.h>

#include "BInteger.h"
#include "PrettyPrinter.h"

namespace bencoding {
namespace tests {

using namespace testing;

class PrettyPrinterTests: public Test {
protected:
	PrettyPrinterTests(): printer(PrettyPrinter::create()) {}

protected:
	std::unique_ptr<PrettyPrinter> printer;
};

//
// Integer representation.
//

TEST_F(PrettyPrinterTests,
PrettyReprOfIntegerZeroIsCorrect) {
	std::shared_ptr<BItem> data(BInteger::create(0));

	EXPECT_EQ("0", printer->getPrettyRepr(data));
}

TEST_F(PrettyPrinterTests,
PrettyReprOfIntegerWithPositiveValueIsCorrect) {
	std::shared_ptr<BItem> data(BInteger::create(13));

	EXPECT_EQ("13", printer->getPrettyRepr(data));
}

TEST_F(PrettyPrinterTests,
PrettyReprOfIntegerWithNegativeValueIsCorrect) {
	std::shared_ptr<BItem> data(BInteger::create(-13));

	EXPECT_EQ("-13", printer->getPrettyRepr(data));
}

} // namespace tests
} // namespace bencoding
