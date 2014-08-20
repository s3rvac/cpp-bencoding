/**
* @file      BListTests.cpp
* @copyright (c) 2014 by Petr Zemek (s3rvac@gmail.com) and contributors
* @license   BSD, see the @c LICENSE file for more details
* @brief     Tests for the BList class.
*/

#include <gtest/gtest.h>

#include "BInteger.h"
#include "BList.h"

namespace bencoding {
namespace tests {

using namespace testing;

class BListTests: public Test {};

TEST_F(BListTests,
ListIsEmptyAfterCreation) {
	auto l = BList::create();

	EXPECT_TRUE(l->empty());
}

TEST_F(BListTests,
ListIsEmptyAfterCreationFromEmptySequenceOfItems) {
	auto l = BList::create({});

	EXPECT_TRUE(l->empty());
}

TEST_F(BListTests,
ListIsNotEmptyAfterItemIsAppendedToEmptyList) {
	auto l = BList::create();
	l->push_back(BInteger::create(1));

	EXPECT_FALSE(l->empty());
}

TEST_F(BListTests,
SizeCorrespondsToNumberOfItemsAppendedIntoList) {
	auto l = BList::create();

	ASSERT_EQ(0, l->size());
	l->push_back(BInteger::create(1));
	ASSERT_EQ(1, l->size());
	l->push_back(BInteger::create(1));
	ASSERT_EQ(2, l->size());
}

TEST_F(BListTests,
ListCreatedFromNonEmptySequenceOfItemsContainsTheItems) {
	std::shared_ptr<BItem> firstItem = BInteger::create(1);
	std::shared_ptr<BItem> secondItem = BInteger::create(2);
	auto l = BList::create({firstItem, secondItem});

	EXPECT_EQ(2, l->size());
	EXPECT_EQ(firstItem, l->front());
	EXPECT_EQ(secondItem, l->back());
}

TEST_F(BListTests,
PopBackCorrectlyRemovesLastItemInNonEmptyList) {
	auto l = BList::create();
	std::shared_ptr<BItem> firstItem = BInteger::create(1);
	l->push_back(firstItem);
	std::shared_ptr<BItem> secondItem = BInteger::create(2);
	l->push_back(secondItem);

	ASSERT_EQ(2, l->size());
	l->pop_back();
	ASSERT_EQ(1, l->size());
	EXPECT_EQ(firstItem, l->front());
}

TEST_F(BListTests,
FrontReturnsFirstItemFromNonEmptyList) {
	auto l = BList::create();
	std::shared_ptr<BItem> firstItem = BInteger::create(1);
	l->push_back(firstItem);
	std::shared_ptr<BItem> secondItem = BInteger::create(2);
	l->push_back(secondItem);

	EXPECT_EQ(firstItem, l->front());
}

TEST_F(BListTests,
FrontReturnsFirstItemFromNonEmptyConstantList) {
	auto l = BList::create();
	std::shared_ptr<BItem> firstItem = BInteger::create(1);
	l->push_back(firstItem);
	std::shared_ptr<BItem> secondItem = BInteger::create(2);
	l->push_back(secondItem);
	std::shared_ptr<const BList> cl(std::move(l));

	EXPECT_EQ(firstItem, cl->front());
}

TEST_F(BListTests,
BackReturnsLastItemFromNonEmptyList) {
	auto l = BList::create();
	std::shared_ptr<BItem> firstItem = BInteger::create(1);
	l->push_back(firstItem);
	std::shared_ptr<BItem> secondItem = BInteger::create(2);
	l->push_back(secondItem);

	EXPECT_EQ(secondItem, l->back());
}

TEST_F(BListTests,
BackReturnsLastItemFromNonEmptyConstantList) {
	auto l = BList::create();
	std::shared_ptr<BItem> firstItem = BInteger::create(1);
	l->push_back(firstItem);
	std::shared_ptr<BItem> secondItem = BInteger::create(2);
	l->push_back(secondItem);
	std::shared_ptr<const BList> cl(std::move(l));

	EXPECT_EQ(secondItem, cl->back());
}

TEST_F(BListTests,
IterationWorksCorrectlyOverEmptyList) {
	auto l = BList::create();

	EXPECT_EQ(l->begin(), l->end());
}

TEST_F(BListTests,
IterationWorksCorrectlyOverListWithTwoItems) {
	auto l = BList::create();
	l->push_back(BInteger::create(1));
	l->push_back(BInteger::create(2));

	auto i = l->begin();
	auto firstItem = (*i)->as<BInteger>();
	ASSERT_TRUE(firstItem != nullptr);
	ASSERT_EQ(1, firstItem->value());

	++i;
	auto secondItem = (*i)->as<BInteger>();
	ASSERT_TRUE(secondItem != nullptr);
	ASSERT_EQ(2, secondItem->value());

	++i;
	ASSERT_EQ(l->end(), i);
}

TEST_F(BListTests,
IterationWorksCorrectlyOverEmptyConstantList) {
	std::unique_ptr<const BList> l = BList::create();

	EXPECT_EQ(l->begin(), l->end());
}

TEST_F(BListTests,
IterationWorksCorrectlyOverConstantListWithTwoItems) {
	auto l = BList::create();
	l->push_back(BInteger::create(1));
	l->push_back(BInteger::create(2));
	std::shared_ptr<const BList> cl(std::move(l));

	auto i = cl->begin();
	auto firstItem = (*i)->as<BInteger>();
	ASSERT_TRUE(firstItem != nullptr);
	ASSERT_EQ(1, firstItem->value());

	++i;
	auto secondItem = (*i)->as<BInteger>();
	ASSERT_TRUE(secondItem != nullptr);
	ASSERT_EQ(2, secondItem->value());

	++i;
	ASSERT_EQ(cl->end(), i);
}

TEST_F(BListTests,
IterationWorksCorrectlyOverEmptyConstantListUsingCPrefixedMethods) {
	std::unique_ptr<const BList> l = BList::create();

	EXPECT_EQ(l->cbegin(), l->cend());
}

TEST_F(BListTests,
IterationWorksCorrectlyOverConstantListWithTwoItemsUsingCPrefixedMethods) {
	auto l = BList::create();
	l->push_back(BInteger::create(1));
	l->push_back(BInteger::create(2));
	std::shared_ptr<const BList> cl(std::move(l));

	auto i = cl->cbegin();
	auto firstItem = (*i)->as<BInteger>();
	ASSERT_TRUE(firstItem != nullptr);
	ASSERT_EQ(1, firstItem->value());

	++i;
	auto secondItem = (*i)->as<BInteger>();
	ASSERT_TRUE(secondItem != nullptr);
	ASSERT_EQ(2, secondItem->value());

	++i;
	ASSERT_EQ(cl->cend(), i);
}

} // namespace tests
} // namespace bencoding
