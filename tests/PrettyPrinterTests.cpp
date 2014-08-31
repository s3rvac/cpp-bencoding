/**
* @file      PrettyPrinterTests.cpp
* @copyright (c) 2014 by Petr Zemek (s3rvac@gmail.com) and contributors
* @license   BSD, see the @c LICENSE file for more details
* @brief     Tests for the PrettyPrinter class.
*/

#include <gtest/gtest.h>

#include "BDictionary.h"
#include "BInteger.h"
#include "BList.h"
#include "BString.h"
#include "PrettyPrinter.h"
#include "TestUtils.h"

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
// Dictionary representation.
//

TEST_F(PrettyPrinterTests,
PrettyReprOfEmptyDictionaryIsCorrect) {
	std::shared_ptr<BDictionary> bDictionary(BDictionary::create());

	EXPECT_EQ("{\n}", printer->getPrettyRepr(bDictionary));
}

TEST_F(PrettyPrinterTests,
PrettyReprOfDictionarysWithOneItemIsCorrect) {
	std::shared_ptr<BDictionary> bDictionary(BDictionary::create());
	(*bDictionary)[BString::create("test")] = BInteger::create(1);

	EXPECT_EQ("{\n    \"test\": 1\n}", printer->getPrettyRepr(bDictionary));
}

TEST_F(PrettyPrinterTests,
PrettyReprOfDictionarysWithTwoItemsIsCorrect) {
	std::shared_ptr<BDictionary> bDictionary(BDictionary::create());
	(*bDictionary)[BString::create("test1")] = BInteger::create(1);
	(*bDictionary)[BString::create("test2")] = BInteger::create(2);

	EXPECT_EQ("{\n    \"test1\": 1,\n    \"test2\": 2\n}",
		printer->getPrettyRepr(bDictionary));
}

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

	EXPECT_EQ("[\n]", printer->getPrettyRepr(bList));
}

TEST_F(PrettyPrinterTests,
PrettyReprOfListWithTwoStringsIsCorrect) {
	std::shared_ptr<BList> bList = BList::create();
	bList->push_back(BString::create("test"));
	bList->push_back(BString::create("hello"));

	EXPECT_EQ("[\n    \"test\",\n    \"hello\"\n]",
		printer->getPrettyRepr(bList));
}

//
// String representation.
//

TEST_F(PrettyPrinterTests,
PrettyReprOfEmptyStringIsCorrect) {
	std::shared_ptr<BItem> data(BString::create(""));

	EXPECT_EQ(R"("")", printer->getPrettyRepr(data));
}

TEST_F(PrettyPrinterTests,
PrettyReprOfNonemptyStringIsCorrect) {
	std::shared_ptr<BItem> data(BString::create("test"));

	EXPECT_EQ(R"("test")", printer->getPrettyRepr(data));
}

TEST_F(PrettyPrinterTests,
QuoteInsideStringIsPrefixedWithBackslash) {
	std::shared_ptr<BItem> data(BString::create("te\"st"));

	EXPECT_EQ(R"("te\"st")", printer->getPrettyRepr(data));
}

//
// Other.
//

TEST_F(PrettyPrinterTests,
GetPrettyReprFunctionWorksAsCreatingPrettyPrinterAndCallingGetPrettyRepr) {
	std::shared_ptr<BDictionary> bDictionary(BDictionary::create());
	(*bDictionary)[BString::create("test")] = BInteger::create(1);

	EXPECT_EQ("{\n    \"test\": 1\n}", getPrettyRepr(bDictionary));
}

} // namespace tests
} // namespace bencoding
