/**
* @file      BDictionaryTests.cpp
* @copyright (c) 2014 by Petr Zemek (s3rvac@gmail.com) and contributors
* @license   BSD, see the @c LICENSE file for more details
* @brief     Tests for the BDictionary class.
*/

#include <gtest/gtest.h>

#include "BDictionary.h"
#include "BInteger.h"
#include "BString.h"

namespace bencoding {
namespace tests {

using namespace testing;

class BDictionaryTests: public Test {};

TEST_F(BDictionaryTests,
DictionaryIsEmptyAfterCreation) {
	auto d = BDictionary::create();

	EXPECT_TRUE(d->empty());
}

TEST_F(BDictionaryTests,
DictionaryIsEmptyAfterCreationFromEmptySequenceOfItems) {
	auto d = BDictionary::create({});

	EXPECT_TRUE(d->empty());
}

TEST_F(BDictionaryTests,
DictionaryIsNotEmptyAfterItemIsAddedToEmptyDictionary) {
	auto d = BDictionary::create();
	(*d)[BString::create("test")] = BInteger::create(1);

	EXPECT_FALSE(d->empty());
}

TEST_F(BDictionaryTests,
SizeCorrespondsToNumberOfItemsInsertedIntoDictionary) {
	auto d = BDictionary::create();

	ASSERT_EQ(0, d->size());
	(*d)[BString::create("test")] = BInteger::create(1);
	ASSERT_EQ(1, d->size());
	(*d)[BString::create("test2")] = BInteger::create(2);
	ASSERT_EQ(2, d->size());
}

TEST_F(BDictionaryTests,
DictionaryCreatedFromNonEmptySequenceOfItemsContainsTheItems) {
	std::shared_ptr<BString> firstKey = BString::create("test1");
	std::shared_ptr<BItem> firstValue = BInteger::create(1);
	std::shared_ptr<BString> secondKey = BString::create("test2");
	std::shared_ptr<BItem> secondValue = BInteger::create(2);
	auto d = BDictionary::create({
		{firstKey, firstValue},
		{secondKey, secondValue}
	});

	EXPECT_EQ(2, d->size());

	auto i = d->begin();
	EXPECT_EQ(firstKey, i->first);
	EXPECT_EQ(firstValue, i->second);

	++i;
	EXPECT_EQ(secondKey, i->first);
	EXPECT_EQ(secondValue, i->second);
}

TEST_F(BDictionaryTests,
ValueIsChangedAfterInsertingAnotherValueForIdenticalKey) {
	auto d = BDictionary::create();

	std::shared_ptr<BString> key = BString::create("test");
	(*d)[key] = BInteger::create(1);
	std::shared_ptr<BItem> newValue = BInteger::create(1);
	(*d)[key] = newValue;
	ASSERT_EQ(newValue, (*d)[key]);
}

TEST_F(BDictionaryTests,
AccessingNonExistingKeyReturnsNullPointer) {
	auto d = BDictionary::create();

	ASSERT_EQ(std::shared_ptr<BItem>(), (*d)[BString::create("test")]);
}

TEST_F(BDictionaryTests,
IterationWorksCorrectlyOverEmptyDictionary) {
	auto d = BDictionary::create();

	EXPECT_EQ(d->begin(), d->end());
}

TEST_F(BDictionaryTests,
IterationWorksCorrectlyOverEmptyConstantDictionary) {
	std::unique_ptr<const BDictionary> d = BDictionary::create();

	EXPECT_EQ(d->begin(), d->end());
}

TEST_F(BDictionaryTests,
IterationWorksCorrectlyOverEmptyConstantDictionaryUsingCPrefixedMethods) {
	std::unique_ptr<const BDictionary> d = BDictionary::create();

	EXPECT_EQ(d->cbegin(), d->cend());
}

TEST_F(BDictionaryTests,
IterationWorksCorrectlyOverDictionaryWithTwoItems) {
	auto d = BDictionary::create();
	// According to the specification, the values in the dictionary should
	// appear in a sorted order by the key values rather than addresses. To
	// test this, we first create the second key, which should have a lower
	// memory address than the first key, which is created after it. In this
	// way, we can test that the returned iterators iterate over the values in
	// the dictionary in a sorted order by the key values rather than
	// addresses.
	std::shared_ptr<BString> secondKey = BString::create("b");
	std::shared_ptr<BItem> secondValue = BInteger::create(2);
	(*d)[secondKey] = secondValue;
	std::shared_ptr<BString> firstKey = BString::create("a");
	std::shared_ptr<BItem> firstValue = BInteger::create(1);
	(*d)[firstKey] = firstValue;

	auto i = d->begin();
	ASSERT_EQ(firstKey, i->first);
	ASSERT_EQ(firstValue, i->second);

	++i;
	ASSERT_EQ(secondKey, i->first);
	ASSERT_EQ(secondValue, i->second);

	++i;
	ASSERT_EQ(d->end(), i);
}

} // namespace tests
} // namespace bencoding
