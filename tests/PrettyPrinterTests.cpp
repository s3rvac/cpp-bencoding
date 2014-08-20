/**
* @file      PrettyPrinterTests.cpp
* @copyright (c) 2014 by Petr Zemek (s3rvac@gmail.com) and contributors
* @license   BSD, see the @c LICENSE file for more details
* @brief     Tests for the PrettyPrinter class.
*/

#include <gtest/gtest.h>

#include "BInteger.h"
#include "BList.h"
#include "BString.h"
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

//
// List representation.
//

TEST_F(PrettyPrinterTests,
PrettyReprOfEmptyListIsCorrect) {
	std::shared_ptr<BList> bList(BList::create());

	EXPECT_EQ("[]", printer->getPrettyRepr(bList));
}

TEST_F(PrettyPrinterTests,
PrettyReprOfListWithTwoStringsIsCorrect) {
	std::shared_ptr<BList> bList = BList::create();
	bList->append(BString::create("test"));
	bList->append(BString::create("hello"));

	EXPECT_EQ("[\"test\", \"hello\"]", printer->getPrettyRepr(bList));
}

//
// String representation.
//

TEST_F(PrettyPrinterTests,
PrettyReprOfEmptyStringIsCorrect) {
	std::shared_ptr<BItem> data(BString::create(""));

	EXPECT_EQ("\"\"", printer->getPrettyRepr(data));
}

TEST_F(PrettyPrinterTests,
PrettyReprOfNonemptyStringIsCorrect) {
	std::shared_ptr<BItem> data(BString::create("test"));

	EXPECT_EQ("\"test\"", printer->getPrettyRepr(data));
}

} // namespace tests
} // namespace bencoding
