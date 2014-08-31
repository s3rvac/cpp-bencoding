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

	void scenarioPrettyReprIsSameForAnyIndentation(std::shared_ptr<BItem> data,
		const std::string refRepr);

protected:
	std::unique_ptr<PrettyPrinter> printer;
};

/**
* @brief Checks that the pretty representation of the given @a data is the same
*        for all levels of indentation, even without indentation.
*/
void PrettyPrinterTests::scenarioPrettyReprIsSameForAnyIndentation(
		std::shared_ptr<BItem> data, const std::string refRepr) {
	EXPECT_EQ(refRepr, printer->getPrettyReprWithoutIndent(data));
	EXPECT_EQ(refRepr, printer->getPrettyRepr(data, ""));
	EXPECT_EQ(refRepr, printer->getPrettyRepr(data, "    "));
}

//
// Dictionary representation.
//

TEST_F(PrettyPrinterTests,
PrettyReprWithoutIndentOfEmptyDictionaryIsCorrect) {
	std::shared_ptr<BDictionary> bDictionary(BDictionary::create());

	EXPECT_EQ("{}", printer->getPrettyReprWithoutIndent(bDictionary));
}

TEST_F(PrettyPrinterTests,
PrettyReprWithIndentOfEmptyDictionaryIsCorrect) {
	std::shared_ptr<BDictionary> bDictionary(BDictionary::create());

	EXPECT_EQ("{\n}", printer->getPrettyRepr(bDictionary, "  "));
}

TEST_F(PrettyPrinterTests,
PrettyReprWithoutIndentOfDictionarysWithOneItemIsCorrect) {
	std::shared_ptr<BDictionary> bDictionary(BDictionary::create());
	(*bDictionary)[BString::create("test")] = BInteger::create(1);

	EXPECT_EQ(R"({"test": 1})",
		printer->getPrettyReprWithoutIndent(bDictionary));
}

TEST_F(PrettyPrinterTests,
PrettyReprWithIndentOfDictionarysWithOneItemIsCorrect) {
	std::shared_ptr<BDictionary> bDictionary(BDictionary::create());
	(*bDictionary)[BString::create("test")] = BInteger::create(1);

	EXPECT_EQ("{\n  \"test\": 1\n}", printer->getPrettyRepr(bDictionary, "  "));
}

TEST_F(PrettyPrinterTests,
PrettyReprWithoutIndentOfDictionarysWithTwoItemsIsCorrect) {
	std::shared_ptr<BDictionary> bDictionary(BDictionary::create());
	(*bDictionary)[BString::create("test1")] = BInteger::create(1);
	(*bDictionary)[BString::create("test2")] = BInteger::create(2);

	EXPECT_EQ(R"({"test1": 1, "test2": 2})",
		printer->getPrettyReprWithoutIndent(bDictionary));
}

TEST_F(PrettyPrinterTests,
PrettyReprWithIndentOfDictionarysWithTwoItemsIsCorrect) {
	std::shared_ptr<BDictionary> bDictionary(BDictionary::create());
	(*bDictionary)[BString::create("test1")] = BInteger::create(1);
	(*bDictionary)[BString::create("test2")] = BInteger::create(2);

	EXPECT_EQ("{\n  \"test1\": 1,\n  \"test2\": 2\n}",
		printer->getPrettyRepr(bDictionary, "  "));
}

//
// Integer representation.
//

TEST_F(PrettyPrinterTests,
PrettyReprOfIntegerZeroIsCorrect) {
	std::shared_ptr<BItem> data(BInteger::create(0));

	ADD_SCOPED_TRACE;
	scenarioPrettyReprIsSameForAnyIndentation(data, "0");
}

TEST_F(PrettyPrinterTests,
PrettyReprOfIntegerWithPositiveValueIsCorrect) {
	std::shared_ptr<BItem> data(BInteger::create(13));

	ADD_SCOPED_TRACE;
	scenarioPrettyReprIsSameForAnyIndentation(data, "13");
}

TEST_F(PrettyPrinterTests,
PrettyReprOfIntegerWithNegativeValueIsCorrect) {
	std::shared_ptr<BItem> data(BInteger::create(-13));

	ADD_SCOPED_TRACE;
	scenarioPrettyReprIsSameForAnyIndentation(data, "-13");
}

//
// List representation.
//

TEST_F(PrettyPrinterTests,
PrettyReprWithoutIndentOfEmptyListIsCorrect) {
	std::shared_ptr<BList> bList(BList::create());

	EXPECT_EQ("[]", printer->getPrettyReprWithoutIndent(bList));
}

TEST_F(PrettyPrinterTests,
PrettyReprWithoutIndentOfListWithTwoStringsIsCorrect) {
	std::shared_ptr<BList> bList = BList::create();
	bList->push_back(BString::create("test"));
	bList->push_back(BString::create("hello"));

	EXPECT_EQ(R"(["test", "hello"])",
		printer->getPrettyReprWithoutIndent(bList));
}

TEST_F(PrettyPrinterTests,
PrettyReprWithIndentOfListWithTwoStringsIsCorrect) {
	std::shared_ptr<BList> bList = BList::create();
	bList->push_back(BString::create("test"));
	bList->push_back(BString::create("hello"));

	EXPECT_EQ("[\n  \"test\",\n  \"hello\"\n]",
		printer->getPrettyRepr(bList, "  "));
}

//
// String representation.
//

TEST_F(PrettyPrinterTests,
PrettyReprOfEmptyStringIsCorrect) {
	std::shared_ptr<BItem> data(BString::create(""));

	ADD_SCOPED_TRACE;
	scenarioPrettyReprIsSameForAnyIndentation(data, R"("")");
}

TEST_F(PrettyPrinterTests,
PrettyReprOfNonemptyStringIsCorrect) {
	std::shared_ptr<BItem> data(BString::create("test"));

	ADD_SCOPED_TRACE;
	scenarioPrettyReprIsSameForAnyIndentation(data, R"("test")");
}

TEST_F(PrettyPrinterTests,
QuoteInsideStringIsPrefixedWithBackslash) {
	std::shared_ptr<BItem> data(BString::create("te\"st"));

	ADD_SCOPED_TRACE;
	scenarioPrettyReprIsSameForAnyIndentation(data, R"("te\"st")");
}

//
// Other.
//

TEST_F(PrettyPrinterTests,
GetPrettyReprFunctionWorksAsCreatingPrettyPrinterAndCallingGetPrettyRepr) {
	std::shared_ptr<BDictionary> bDictionary(BDictionary::create());
	(*bDictionary)[BString::create("test")] = BInteger::create(1);

	EXPECT_EQ("{\n  \"test\": 1\n}", getPrettyRepr(bDictionary, "  "));
}

TEST_F(PrettyPrinterTests,
GetPrettyReprWithoutIndentFunctionWorksAsCreatingPrettyPrinterAndCallingGetPrettyReprWithoutIndent) {
	std::shared_ptr<BDictionary> bDictionary(BDictionary::create());
	(*bDictionary)[BString::create("test")] = BInteger::create(1);

	EXPECT_EQ("{\"test\": 1}", getPrettyReprWithoutIndent(bDictionary));
}

} // namespace tests
} // namespace bencoding
